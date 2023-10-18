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
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Verifier.h>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

void LLVM_Visitor::visitBinaryExpression(BinaryExpression *expression) {
  std::string type = expression->getOPType();
  expression->getRHS()->accept(this);
  llvm::Value *R = llvm_result;
  expression->getLHS()->accept(this);
  llvm::Value *L = llvm_result;

  if (L == nullptr || R == nullptr) {
    throw std::invalid_argument("Null pointer argument");
  }

  if (type == "+") {
    llvm_result = Builder->CreateAdd(L, R, "addtmp");
  } else if (type == "-") {
    llvm_result = Builder->CreateSub(L, R, "subtmp");
  } else if (type == "*") {
    llvm_result = Builder->CreateMul(L, R, "multmp");
  } else if (type == "/") {
    llvm_result = Builder->CreateSDiv(L, R, "divtmp");
  } else if (type == "%") {
    llvm_result = Builder->CreateSRem(L, R, "modtmp");
  } else if (type == "<") {
    llvm_result = Builder->CreateICmpSLT(L, R, "lttmp");
  } else if (type == ">") {
    llvm_result = Builder->CreateICmpSGT(L, R, "gttmp");
  } else if (type == "==") {
    llvm_result = Builder->CreateICmpEQ(L, R, "eqtmp");
  } else if (type == "!=") {
    llvm_result = Builder->CreateICmpNE(L, R, "netmp");
  } else {
    throw std::invalid_argument("Invalid operator");
  }
}

void LLVM_Visitor::visitTerminalExpression(TerminalExpression *terminal) {
  switch (terminal->getType()) {
  case INT:
    llvm_result = llvm::ConstantInt::get(
        *TheContext, llvm::APInt(64, terminal->getIntValue()));
    break;
  case BOOLEAN:
    llvm_result = llvm::ConstantInt::get(
        *TheContext, llvm::APInt(1, terminal->getBoolValue()));
    break;
  }
}

void LLVM_Visitor::visitBlockExpression(BlockExpression *block) {
  symbolTableStack.push({});
  for (auto &expr : block->getInstructions()) {
    expr->accept(this);
    if (dynamic_cast<ReturnExpression *>(expr) != nullptr) {
      break;
    }
  }
  symbolTableStack.pop();
}

void LLVM_Visitor::visitReturnExpression(ReturnExpression *returnExpr) {
  returnExpr->getExpr()->accept(this);
}

void LLVM_Visitor::visitIfExpression(IfExpression *ifExpression) {
    llvm::Function *function = Builder->GetInsertBlock()->getParent();

    if (!ifExpression->getElseBlock()) {
        ifExpression->getCondition()->accept(this);
        llvm::Value *cond = llvm_result;

        llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(*TheContext, "then", function);
        llvm::BasicBlock *afterIfBB = llvm::BasicBlock::Create(*TheContext, "afterIf", function);

        Builder->CreateCondBr(cond, thenBB, afterIfBB);

        Builder->SetInsertPoint(thenBB);
        ifExpression->getThenBlock()->accept(this);
        Builder->CreateBr(afterIfBB);

        Builder->SetInsertPoint(afterIfBB);
        // Assuming you have a default value if the if condition is not true.
        llvm_result = cond;
        return;
    }

    llvm::BasicBlock *finalMergeBB = llvm::BasicBlock::Create(*TheContext, "finalMerge", function);

    // Vectors to track blocks and their corresponding values.
    std::vector<llvm::BasicBlock*> blocks;
    std::vector<llvm::Value*> values;

    while (ifExpression) {
        ifExpression->getCondition()->accept(this);
        llvm::Value *cond = llvm_result;

        llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(*TheContext, "then", function);
        llvm::BasicBlock *nextCondBB = llvm::BasicBlock::Create(*TheContext, "nextCond", function);

        Builder->CreateCondBr(cond, thenBB, nextCondBB);

        // Handle the 'then' part.
        Builder->SetInsertPoint(thenBB);
        ifExpression->getThenBlock()->accept(this);
        llvm::Value *thenValue = llvm_result;
        blocks.push_back(thenBB);
        values.push_back(thenValue);
        Builder->CreateBr(finalMergeBB);

        // Process the 'else' part.
        Builder->SetInsertPoint(nextCondBB);
        if (IfExpression *elseIfExpr = dynamic_cast<IfExpression*>(ifExpression->getElseBlock())) {
            ifExpression = elseIfExpr; 
        } else {
            if (ifExpression->getElseBlock()) {
                ifExpression->getElseBlock()->accept(this);
                blocks.push_back(nextCondBB);
                values.push_back(llvm_result);
            }
            Builder->CreateBr(finalMergeBB);
            break;
        }
    }

    // Final PHI node creation.
    Builder->SetInsertPoint(finalMergeBB);
    llvm::PHINode *phi = Builder->CreatePHI(llvm::Type::getInt64Ty(*TheContext), blocks.size(), "iftmp");
    for (size_t i = 0; i < blocks.size(); i++) {
        phi->addIncoming(values[i], blocks[i]);
    }

    llvm_result = phi;
}

void LLVM_Visitor::visitVariableAssignmentExpression(
    VariableAssignmentExpression *variable) {
  std::cout << "visit var assign \n";
  // get value to be stored
  BaseExpression *variableValue = variable->getValueExpression();
  variableValue->accept(this);
  std::string variableName = variable->getVariable()->getName();
  // create variable in memmory
  // llvm::Function *parentFunction = Builder->GetInsertBlock()->getParent();

  llvm::AllocaInst *varAllocation = (*Builder).CreateAlloca(
      llvm::Type::getInt64Ty(*TheContext), nullptr,
      variableName); // CreateEntryBlockAlloca(parentFunction, variableName);
  symbolTableStack.top()[variableName] = varAllocation;

  // store value in variable
  Builder->CreateStore(llvm_result, varAllocation);

  if (variable->isVarMutable()) {
    mutableVars.insert(variableName);
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
    arg.setName(argNames[Idx++]);
    llvm::AllocaInst *alloca =
        CreateEntryBlockAlloca(function, std::string(arg.getName()));
    Builder->CreateAlignedStore(&arg, alloca, llvm::Align(8));
    symbolTableStack.top()[std::string(arg.getName())] = alloca;
  }

  funcDeclExpr->getBody()->accept(this);

  Builder->CreateRet(llvm_result);

  llvm::verifyFunction(*function);

  symbolTableStack.pop();
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

llvm::Type *LLVM_Visitor::getLLVMType(std::string type) {
  if (type == "int") {
    return llvm::Type::getInt64Ty(*TheContext);
  } else {
    throw std::runtime_error("Unknown Type:" + type);
  }

  return llvm::Type::getVoidTy(*TheContext);
}
