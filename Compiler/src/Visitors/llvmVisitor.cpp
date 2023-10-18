#include "Visitors/llvmVisitor.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"

#include "Expressions/ReturnExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/ifExpression.hpp"
#include "Expressions/programExpression.hpp"
#include "Visitors/baseVisitor.hpp"

#include <iostream>
#include <llvm-18/llvm/IR/BasicBlock.h>
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/Function.h>
#include <llvm-18/llvm/IR/Instruction.h>
#include <llvm-18/llvm/IR/Verifier.h>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

void LLVM_Visitor::visitBinaryExpression(BinaryExpression *expression) {
  char type = expression->getOPType();
  expression->getRHS()->accept(this);
  llvm::Value *R = llvm_result;
  expression->getLHS()->accept(this);
  llvm::Value *L = llvm_result;

  switch (type) {
  case '+':
    if (expression->getType() != "float") {
      llvm_result = Builder->CreateAdd(L, R, "subtmp");
    } else {
      llvm_result = Builder->CreateFAdd(L, R, "subtmp");
    }
    break;
  case '-':
    if (expression->getType() != "float") {
      llvm_result = Builder->CreateSub(L, R, "subtmp");
    } else {
      llvm_result = Builder->CreateFSub(L, R, "subtmp");
    }
    break;
  case '*':
    if (expression->getType() != "float") {
      llvm_result = Builder->CreateMul(L, R, "subtmp");
    } else {
      llvm_result = Builder->CreateFMul(L, R, "subtmp");
    }
    break;
  case '/':
    if (expression->getType() != "float") {
      llvm_result = Builder->CreateSDiv(L, R, "divtmp");
    } else {
      llvm_result = Builder->CreateFDiv(L, R, "subtmp");
    }
    break;
  case '%':
    if (expression->getType() != "float") {
      llvm_result = Builder->CreateSRem(L, R, "subtmp");
    } else {
      llvm_result = Builder->CreateFRem(L, R, "subtmp");
    }
    break;
  default:
    throw std::invalid_argument("Unknown Binary opperator");
  }
}

void LLVM_Visitor::visitTerminalExpression(TerminalExpression *terminal) {
  if (terminal->getType() == "int") {
    llvm_result = llvm::ConstantInt::get(
        *TheContext, llvm::APInt(64, terminal->getIntValue()));
  } else if (terminal->getType() == "boolean") {
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
  symbolTableStack.push({});
  mutableVars.push({});
  for (auto &expr : block->getInstructions()) {
    expr->accept(this);
    if (dynamic_cast<ReturnExpression *>(expr) != nullptr) {
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

  ifExpression->getCondition()->accept(this);
  llvm::Value *cond = llvm_result;

  llvm::BasicBlock *thenBB =
      llvm::BasicBlock::Create(*TheContext, "then", function);
  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(*TheContext, "mergeBB", function);
  llvm::BasicBlock *elseBB = nullptr;

  if (ifExpression->getElseBlock()) {
    llvm::BasicBlock *elseBB =
        llvm::BasicBlock::Create(*TheContext, "else", function);
    Builder->CreateCondBr(cond, thenBB, elseBB);
  } else {
    Builder->CreateCondBr(cond, thenBB, mergeBB);
  }

  Builder->SetInsertPoint(thenBB);
  ifExpression->getThenBlock()->accept(this);

  llvm::Value *thenValue = llvm_result;
  Builder->CreateBr(mergeBB);

  if (elseBB != nullptr) {
    Builder->SetInsertPoint(elseBB);
    ifExpression->getElseBlock()->accept(this);
    llvm::Value *elseValue = llvm_result;
    Builder->CreateBr(mergeBB);

    Builder->SetInsertPoint(mergeBB);
    llvm::PHINode *phi =
        Builder->CreatePHI(llvm::Type::getInt64Ty(*TheContext), 2, "iftmp");
    phi->addIncoming(thenValue, thenBB);
    phi->addIncoming(elseValue, elseBB);

    llvm_result = phi;
  } else {
    Builder->SetInsertPoint(mergeBB);
    llvm_result = thenValue;
  }
}

void LLVM_Visitor::visitVariableAssignmentExpression(
    VariableAssignmentExpression *variable) {
  // get value to be stored
  BaseExpression *variableValue = variable->getValueExpression();
  variableValue->accept(this);
  std::string variableName = variable->getVariable()->getName();
  // create variable in memmory
  llvm::Function *parentFunction = Builder->GetInsertBlock()->getParent();

  llvm::AllocaInst *varAllocation = CreateEntryBlockAlloca(
      parentFunction, variableName, getLLVMType(variable->getType()));
  symbolTableStack.top()[variableName] = varAllocation;

  // store value in variable
  Builder->CreateStore(llvm_result, varAllocation);

  if (variable->isVarMutable()) {
    mutableVars.top().insert(variableName);
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
  llvm_result =
      Builder->CreateAlignedLoad(loadedVar->getAllocatedType(), loadedVar,
                                 llvm::Align(8), variable->getName().c_str());
}

void LLVM_Visitor::visitFunctionDeclaration(FunctionDeclaration *funcDeclExpr) {
  symbolTableStack.push({});
  mutableVars.push({});

  std::vector<llvm::Type *> argTypes;
  std::vector<std::string> argNames;

  for (auto &arg : funcDeclExpr->getArgs()) {
    argTypes.push_back(getLLVMType(arg.first));
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
  }

  funcDeclExpr->getBody()->accept(this);

  Builder->CreateRet(llvm_result);

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

  llvm::Function *mainFunc = TheModule->getFunction("main");
  if (!mainFunc) {
    throw std::runtime_error("missing main function");
  }

  llvm::FunctionType *entryFuncType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext), false);
  llvm::Function *entryFunc =
      llvm::Function::Create(entryFuncType, llvm::Function::ExternalLinkage,
                             "_start", TheModule.get());

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", entryFunc);
  Builder->SetInsertPoint(entryBlock);

  Builder->CreateCall(mainFunc);
  Builder->CreateRetVoid();

  llvm::verifyFunction(*entryFunc);
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

  Builder->CreateStore(llvm_result, loadedVar);
}

llvm::Type *LLVM_Visitor::getLLVMType(std::string type) {
  if (type == "int") {
    return llvm::Type::getInt64Ty(*TheContext);
  } else if (type == "float") {
    return llvm::Type::getFP128Ty(*TheContext);
  } else if (type == "char") {
    return llvm::Type::getInt8Ty(*TheContext);
  } else if (type == "boolean") {
    return llvm::Type::getInt1Ty(*TheContext);
  } else {
    throw std::runtime_error("Unknown Type:" + type);
  }

  return llvm::Type::getVoidTy(*TheContext);
}
