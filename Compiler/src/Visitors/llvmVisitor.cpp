#include "Visitors/llvmVisitor.hpp"
#include "Expressions/ReturnExpression.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/ifExpression.hpp"
#include "Expressions/programExpression.hpp"
#include "Expressions/referenceAssignmentExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"
#include "Visitors/baseVisitor.hpp"

#include <iostream>
#include <llvm-18/llvm/ADT/APFloat.h>
#include <llvm-18/llvm/IR/BasicBlock.h>
#include <llvm-18/llvm/IR/Constant.h>
#include <llvm-18/llvm/IR/Constants.h>
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/Function.h>
#include <llvm-18/llvm/IR/Instruction.h>
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Verifier.h>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

void LLVM_Visitor::visitBinaryExpression(BinaryExpression *expression) {
  std::string type = expression->getOPType();
  std::string exprType = expression->getType();

  if (dispatchTable.empty()) {
    initializeBinaryOperatorFunctionTable();
  }

  expression->getRHS()->accept(this);
  llvm::Value *R = llvm_result;
  expression->getLHS()->accept(this);
  llvm::Value *L = llvm_result;

  if (L == nullptr || R == nullptr) {
    throw std::invalid_argument("Null Pointer Argument");
  }

  if (L->getType()->isPointerTy()) {
    L = Builder->CreatePointerCast(L,
                                   getLLVMType(expression->getLHS()->getType()),
                                   L->getName().str() + "_casted");
  }

  if (R->getType()->isPointerTy()) {
    R = Builder->CreatePointerCast(L,
                                   getLLVMType(expression->getRHS()->getType()),
                                   R->getName().str() + "_casted");
  }

  auto dispatchMapIt = dispatchTable.find(type);
  if (dispatchMapIt != dispatchTable.end()) {
    auto typeIt = dispatchMapIt->second.find(exprType);
    if (typeIt != dispatchMapIt->second.end()) {
      llvm_result = typeIt->second(L, R);
    } else {
      throw std::invalid_argument("Unknown Expression Type");
    }
  } else {
    throw std::invalid_argument("Unknown Operator");
  }
}

void LLVM_Visitor::visitTerminalExpression(TerminalExpression *terminal) {
  if (terminal->getType() == "int") {
    llvm_result = llvm::ConstantInt::get(
        *TheContext, llvm::APInt(64, terminal->getIntValue()));
  } else if (terminal->getType() == "bool") {
    llvm_result = llvm::ConstantInt::get(
        *TheContext, llvm::APInt(1, terminal->getBoolValue()));
  } else if (terminal->getType() == "float") {
    llvm_result = llvm::ConstantFP::get(
        *TheContext, llvm::APFloat(terminal->getFloatValue()));
  } else if (terminal->getType() == "char") {
    llvm_result = llvm::ConstantInt::get(
        *TheContext, llvm::APInt(8, terminal->getBoolValue()));
  }
}

void LLVM_Visitor::visitBlockExpression(BlockExpression *block) {
  if (Builder->GetInsertBlock()->getTerminator()) {
    return;
  }

  symbolTableStack.push({});
  mutableVars.push({});
  for (auto &expr : block->getInstructions()) {
    expr->accept(this);
    if (dynamic_cast<ReturnExpression *>(expr) != nullptr) {
      Builder->CreateRet(llvm_result);
      break;
    }
  }
  symbolTableStack.pop();
  mutableVars.pop();
}

void LLVM_Visitor::visitReturnExpression(ReturnExpression *returnExpr) {
  returnExpr->getExpr()->accept(this);
}

void LLVM_Visitor::visitIfExpression(IfExpression *ifExpression) {
  llvm::Function *function = Builder->GetInsertBlock()->getParent();

  if (!ifExpression->getElseBlock()) {
    ifExpression->getCondition()->accept(this);
    llvm::Value *cond = llvm_result;

    llvm::BasicBlock *thenBB =
        llvm::BasicBlock::Create(*TheContext, "then", function);
    llvm::BasicBlock *afterIfBB =
        llvm::BasicBlock::Create(*TheContext, "afterIf", function);

    Builder->CreateCondBr(cond, thenBB, afterIfBB);

    Builder->SetInsertPoint(thenBB);
    ifExpression->getThenBlock()->accept(this);

    if (!Builder->GetInsertBlock()->getTerminator()) {
      Builder->CreateBr(afterIfBB);
    }

    Builder->SetInsertPoint(afterIfBB);

    // Assuming you have a default value if the if condition is not true.
    llvm_result = cond;

    return;
  }

  llvm::BasicBlock *finalMergeBB =
      llvm::BasicBlock::Create(*TheContext, "finalMerge", function);

  // Vectors to track blocks and their corresponding values.
  std::vector<llvm::BasicBlock *> blocks;
  std::vector<llvm::Value *> values;

  while (ifExpression) {
    ifExpression->getCondition()->accept(this);
    llvm::Value *cond = llvm_result;

    llvm::BasicBlock *thenBB =
        llvm::BasicBlock::Create(*TheContext, "then", function);
    llvm::BasicBlock *nextCondBB =
        llvm::BasicBlock::Create(*TheContext, "nextCond", function);

    Builder->CreateCondBr(cond, thenBB, nextCondBB);

    // Handle the 'then' part.
    Builder->SetInsertPoint(thenBB);
    ifExpression->getThenBlock()->accept(this);

    if (!Builder->GetInsertBlock()->getTerminator()) {
      llvm::Value *thenValue = llvm_result;
      blocks.push_back(thenBB);
      values.push_back(thenValue);
      Builder->CreateBr(finalMergeBB);
    }

    // Process the 'else' part.
    Builder->SetInsertPoint(nextCondBB);
    if (IfExpression *elseIfExpr =
            dynamic_cast<IfExpression *>(ifExpression->getElseBlock())) {
      ifExpression = elseIfExpr;
    } else {
      ifExpression->getElseBlock()->accept(this);
      if (!Builder->GetInsertBlock()->getTerminator()) {
        blocks.push_back(nextCondBB);
        values.push_back(llvm_result);
        Builder->CreateBr(finalMergeBB);
      }
      break;
    }
  }

  // Final PHI node creation.
  Builder->SetInsertPoint(finalMergeBB);
  llvm::PHINode *phi = Builder->CreatePHI(getLLVMType(ifExpression->getType()),
                                          blocks.size(), "iftmp");
  for (size_t i = 0; i < blocks.size(); i++) {
    phi->addIncoming(values[i], blocks[i]);
  }

  if (Builder->GetInsertBlock()->getTerminator()) {
    Builder->CreateRet(phi);
  }

  llvm_result = phi;
}

void LLVM_Visitor::visitVariableAssignmentExpression(
    VariableAssignmentExpression *variable) {
  // get value to be stored
  BaseExpression *variableValue = variable->getValueExpression();
  variableValue->accept(this);
  std::string variableName = variable->getVariable()->getName();
  // create variable in memmory

  if (llvm_result->getType()->isPointerTy()) {
    llvm_result->dump();
    llvm_result = Builder->CreatePointerCast(
        llvm_result, getLLVMType(variable->getType()),
        variable->getVariable()->getName().c_str());
    llvm_result->dump();
    std::cout << variable->getType() << std::endl;
  }

  llvm::Function *parentFunction = Builder->GetInsertBlock()->getParent();

  llvm::AllocaInst *varAllocation = CreateEntryBlockAlloca(
      parentFunction, variableName, getLLVMType(variable->getType()));
  symbolTableStack.top()[variableName] = varAllocation;

  // store value in variable
  Builder->CreateAlignedStore(llvm_result, varAllocation, llvm::Align(8));

  if (variable->isVarMutable()) {
    mutableVars.top().insert(variableName);
  }
}

void LLVM_Visitor::visitReferenceAssignmentExpression(
    ReferenceAssignmentExpression *expression) {
  llvm::Function *parentFunction = Builder->GetInsertBlock()->getParent();

  llvm::Value *referenceValue =
      symbolTableStack.top()[expression->getReferenceIdentifier()];

  llvm::AllocaInst *pointerToReference =
      Builder->CreateAlloca(referenceValue->getType()->getPointerTo(), 0,
                            expression->getIdentifier().c_str());

  Builder->CreateStore(referenceValue, pointerToReference);

  expression->setReferenceValue(pointerToReference);

  symbolTableStack.top()[expression->getIdentifier()] = pointerToReference;

  if (expression->isVarMutable()) {
    mutableVars.top().insert(expression->getIdentifier());
  }
}

void LLVM_Visitor::visitVariableExpression(VariableExpression *variable) {

  llvm::AllocaInst *loadedVar = nullptr;

  std::stack<std::unordered_map<std::string, llvm::AllocaInst *>> tmpStack =
      symbolTableStack;

  while (!tmpStack.empty()) {
    if (tmpStack.top().find(variable->getName()) != tmpStack.top().end()) {
      loadedVar = tmpStack.top()[variable->getName()];
      break;
    }
    tmpStack.pop();
  }

  if (!loadedVar) {
    throw std::invalid_argument("Variable with name: '" + variable->getName() +
                                "' not found");
  }

  if (loadedVar->getAllocatedType()->isPointerTy() ||
      variable->getIsReference()) {
    llvm::Value *tmp = Builder->CreateLoad(loadedVar->getType(), loadedVar,
                                           variable->getName().c_str());
    llvm_result =
        Builder->CreateLoad(tmp->getType(), tmp, variable->getName().c_str());
  } else {
    llvm_result =
        Builder->CreateAlignedLoad(loadedVar->getAllocatedType(), loadedVar,
                                   llvm::Align(8), variable->getName().c_str());
  }
}

void LLVM_Visitor::visitFunctionDeclaration(FunctionDeclaration *funcDeclExpr) {
  symbolTableStack.push({});
  mutableVars.push({});

  std::vector<llvm::Type *> argTypes;
  std::vector<std::string> argNames;

  for (auto &arg : funcDeclExpr->getArgs()) {
    if (arg.first.rfind("&", 0) == 0) {
      argTypes.push_back(getLLVMType(arg.first)->getPointerTo());
    } else {
      argTypes.push_back(getLLVMType(arg.first));
    }
    argNames.push_back(arg.second);
  }

  llvm::Type *returnType = getLLVMType(funcDeclExpr->getReturnType());
  llvm::FunctionType *funcType;

  funcType = llvm::FunctionType::get(returnType, argTypes, false);

  auto *function =
      llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                             funcDeclExpr->getName(), TheModule.get());

  auto *block = llvm::BasicBlock::Create(*TheContext, "entry", function);
  Builder->SetInsertPoint(block);

  auto Idx = 0;
  for (auto &arg : function->args()) {
    llvm::Type *argType = argTypes[Idx];
    arg.setName(argNames[Idx++]);
    llvm::AllocaInst *alloca =
        CreateEntryBlockAlloca(function, std::string(arg.getName()), argType);
    Builder->CreateAlignedStore(&arg, alloca, llvm::Align(8));
    symbolTableStack.top()[std::string(arg.getName())] = alloca;
    mutableVars.top().insert(argNames[Idx - 1]);
  }

  funcDeclExpr->getBody()->accept(this);

  llvm::verifyFunction(*function);

  symbolTableStack.pop();
  mutableVars.pop();
}

void LLVM_Visitor::visitFunctionCall(FunctionCall *funcCallExpr) {
  llvm::Function *function = TheModule->getFunction(funcCallExpr->getName());

  std::cout << "retrieved test function" << std::endl;

  if (!function) {
    throw std::runtime_error("No known function by that name");
  }

  std::vector<llvm::Value *> args;
  for (auto &arg : funcCallExpr->getArgs()) {
    arg->accept(this);
    args.push_back(llvm_result);
  }

  llvm_result = Builder->CreateCall(function, args, "calltmp");
}

void LLVM_Visitor::visitProgramExpression(ProgramExpression *program) {
  for (auto funcDecl : program->getFunctions()) {
    funcDecl->accept(this);
  }
}

void LLVM_Visitor::visitVariableReassignmentExpression(
    VariableReassignmentExpression *variable) {
  variable->getValueExpression()->accept(this);

  llvm::AllocaInst *loadedVar = nullptr;

  std::stack<std::unordered_map<std::string, llvm::AllocaInst *>> tmpStack =
      symbolTableStack;
  std::stack<std::unordered_set<std::string>> tmpMutableVars = mutableVars;

  while (!tmpStack.empty()) {
    if (tmpStack.top().find(variable->getVariable()->getName()) !=
        tmpStack.top().end()) {
      loadedVar = tmpStack.top()[variable->getVariable()->getName()];
      if (tmpMutableVars.top().find(variable->getVariable()->getName()) ==
          tmpMutableVars.top().end()) {
        throw std::runtime_error("Reassignment of immutable variable.");
      }
      break;
    }
    tmpStack.pop();
    tmpMutableVars.pop();
  }

  if (!loadedVar) {
    throw std::invalid_argument("Variable with name: '" +
                                variable->getVariable()->getName() +
                                "' not found");
  }

  if (loadedVar->getAllocatedType()->isPointerTy() ||
      variable->getVariable()->getIsReference()) {
    llvm::Value *tmp =
        Builder->CreateLoad(loadedVar->getType(), loadedVar,
                            variable->getVariable()->getName().c_str());
    Builder->CreateStore(llvm_result, tmp);
  } else {
    Builder->CreateStore(llvm_result, loadedVar);
  }
}

llvm::Type *LLVM_Visitor::getLLVMType(std::string type) {
  if (type == "int") {
    return llvm::Type::getInt64Ty(*TheContext);
  } else if (type == "float") {
    return llvm::Type::getFloatTy(*TheContext);
  } else if (type == "char") {
    return llvm::Type::getInt8Ty(*TheContext);
  } else if (type == "bool") {
    return llvm::Type::getInt1Ty(*TheContext);
  } else if (type == "&int") {
    return llvm::Type::getInt64Ty(*TheContext);
  } else if (type == "&float") {
    return llvm::Type::getFloatTy(*TheContext);
  } else if (type == "&char") {
    return llvm::Type::getInt8Ty(*TheContext);
  } else if (type == "&bool") {
    return llvm::Type::getInt64Ty(*TheContext);
  } else {
    throw std::runtime_error("Unknown Type:" + type);
  }
  return llvm::Type::getVoidTy(*TheContext);
}

void LLVM_Visitor::initializeBinaryOperatorFunctionTable() {
  dispatchTable["+"]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateAdd(L, R, "addtmp");
  };
  dispatchTable["+"]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateAdd(L, R, "addtmp");
  };
  dispatchTable["+"]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateAdd(L, R, "addtmp");
  };
  dispatchTable["+"]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFAdd(L, R, "addtmp");
  };

  dispatchTable["-"]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSub(L, R, "subtmp");
  };
  dispatchTable["-"]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSub(L, R, "subtmp");
  };
  dispatchTable["-"]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSub(L, R, "subtmp");
  };
  dispatchTable["-"]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFSub(L, R, "subtmp");
  };

  dispatchTable["*"]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateMul(L, R, "multmp");
  };
  dispatchTable["*"]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateMul(L, R, "multmp");
  };
  dispatchTable["*"]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateMul(L, R, "multmp");
  };
  dispatchTable["*"]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFMul(L, R, "multmp");
  };

  dispatchTable["/"]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSDiv(L, R, "divtmp");
  };
  dispatchTable["/"]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSDiv(L, R, "divtmp");
  };
  dispatchTable["/"]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSDiv(L, R, "divtmp");
  };
  dispatchTable["/"]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFDiv(L, R, "divtmp");
  };

  dispatchTable["%"]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSRem(L, R, "modtmp");
  };
  dispatchTable["%"]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSRem(L, R, "modtmp");
  };
  dispatchTable["%"]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateSRem(L, R, "modtmp");
  };
  dispatchTable["%"]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFRem(L, R, "modtmp");
  };

  dispatchTable["<"]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpSLT(L, R, "lltmp");
  };
  dispatchTable["<"]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpSLT(L, R, "lltmp");
  };
  dispatchTable["<"]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpSLT(L, R, "lltmp");
  };
  dispatchTable["<"]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFCmpOLT(L, R, "lltmp");
  };

  dispatchTable[">"]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpSGT(L, R, "gttmp");
  };
  dispatchTable[">"]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpSGT(L, R, "gttmp");
  };
  dispatchTable[">"]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpSGT(L, R, "gttmp");
  };
  dispatchTable[">"]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFCmpOGT(L, R, "gttmp");
  };

  dispatchTable["=="]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpEQ(L, R, "eqtmp");
  };
  dispatchTable["=="]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpEQ(L, R, "eqtmp");
  };
  dispatchTable["=="]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpEQ(L, R, "eqtmp");
  };
  dispatchTable["=="]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFCmpOEQ(L, R, "eqtmp");
  };

  dispatchTable["!="]["int"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpNE(L, R, "neqtmp");
  };
  dispatchTable["!="]["bool"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpNE(L, R, "gttmp");
  };
  dispatchTable["!="]["char"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateICmpNE(L, R, "gttmp");
  };
  dispatchTable["!="]["float"] = [this](llvm::Value *L, llvm::Value *R) {
    return Builder->CreateFCmpONE(L, R, "neqtmp");
  };
}
