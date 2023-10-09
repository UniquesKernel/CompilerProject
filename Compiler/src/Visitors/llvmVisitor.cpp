#include "Visitors/llvmVisitor.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"

#include "Expressions/blockExpression.hpp"
#include "Expressions/ReturnExpression.hpp"
#include "Expressions/ifExpression.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/functionCall.hpp"
#include "Visitors/baseVisitor.hpp"
#include "Expressions/variableExpression.hpp"

#include <iostream>
#include <llvm-18/llvm/IR/BasicBlock.h>
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/Instruction.h>
#include <optional>
#include <stdexcept>

void LLVM_Visitor::visitBinaryExpression(BinaryExpression *expression) {
  char type = expression->getType();
  expression->getRHS()->accept(this);
  llvm::Value *R = llvm_result;


  if(type == '=') { // check if assigning to a variable
        VariableExpression *L = static_cast<VariableExpression*>(expression->getLHS());
    if (!L) {
      throw std::invalid_argument("'=' must assign to  a variable");
    }

    if(mutableVars.find(L->getName()) == mutableVars.end()){
      throw std::invalid_argument("Assignment to immutable variable. is not allowed");
    }

    llvm::Value * variable = symbolTable[L->getName()];
    Builder->CreateStore(R, variable);

    llvm_result = R;
  }

  expression->getLHS()->accept(this);
  llvm::Value *L = llvm_result;

  expression->getLHS()->accept(this);
  llvm::Value *L = llvm_result;

  switch (type) {
  case '+':
    llvm_result = Builder->CreateAdd(L, R, "addtmp");
    break;
  case '-':
    llvm_result = Builder->CreateSub(L, R, "subtmp");
    break;
  case '*':
    llvm_result = Builder->CreateMul(L, R, "multmp");
    break;
  case '/':
    llvm_result = Builder->CreateSDiv(L, R, "divtmp");
    break;
  case '%':
    llvm_result = Builder->CreateSRem(L, R, "modtmp");
    break;
  default:
    throw std::invalid_argument("PANIC");
  }
}

void LLVM_Visitor::visitTerminalExpression(TerminalExpression *terminal) {
  switch(terminal->getType()) {
    case INT:
      llvm_result = llvm::ConstantInt::get(*TheContext, llvm::APInt(64, terminal->getIntValue()));
      break;
    case BOOLEAN:
      llvm_result = llvm::ConstantInt::get(*TheContext, llvm::APInt(1, terminal->getBoolValue()));
      break;
  }
}

void LLVM_Visitor::visitBlockExpression(BlockExpression *block) {
  for (auto& expr : block->getInstructions()) {
    expr->accept(this);
    if (dynamic_cast<ReturnExpression*>(expr) != nullptr) {
      break;
    }
  }
}

void LLVM_Visitor::visitReturnExpression(ReturnExpression *returnExpr) {
  returnExpr->getExpr()->accept(this);
}

void LLVM_Visitor::visitIfExpression(IfExpression *ifExpression) {
  llvm::Function* function = Builder->GetInsertBlock()->getParent();


  ifExpression->getCondition()->accept(this);
  llvm::Value* cond = llvm_result;

  llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(*TheContext, "then", function);
  llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(*TheContext, "else", function);
  llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(*TheContext, "mergeBB", function);

  Builder->CreateCondBr(cond, thenBB, elseBB);

  Builder->SetInsertPoint(thenBB);
  ifExpression->getThenBlock()->accept(this);

  llvm::Value* thenValue = llvm_result;
  Builder->CreateBr(mergeBB);

  Builder->SetInsertPoint(elseBB);
  ifExpression->getElseBlock()->accept(this);
  llvm::Value* elseValue = llvm_result;
  Builder->CreateBr(mergeBB);


  Builder->SetInsertPoint(mergeBB);
  llvm::PHINode* phi = Builder->CreatePHI(llvm::Type::getInt64Ty(*TheContext), 2, "iftmp");
  phi->addIncoming(thenValue, thenBB);
  phi->addIncoming(elseValue, elseBB);

  llvm_result = phi;
}


void LLVM_Visitor::visitVariableAssignmentExpression(VariableAssignmentExpression *variable) {
  // get value to be stored
  BaseExpression* variableValue = variable->getValueExpression();
  variableValue->accept(this);
  std::string variableName = variable->getVariable()->getName();
  // create variable in memmory
  //llvm::Function *parentFunction = Builder->GetInsertBlock()->getParent();

  std::cout << " 1 \n";
  llvm::AllocaInst* varAllocation = (*Builder).CreateAlloca(llvm::Type::getInt64Ty(*TheContext), nullptr, variableName);//CreateEntryBlockAlloca(parentFunction, variableName);
  symbolTable[variableName] = varAllocation;

  //store value in variable
  Builder->CreateStore(llvm_result, varAllocation);

  if(variable->isVarMutable()){ mutableVars.insert(variableName); }
}

void LLVM_Visitor::visitVariableExpression(VariableExpression *variable) {
  std::cout << "visit var \n";
  llvm::AllocaInst* loadedVar = symbolTable[variable->getName()];
  if(!loadedVar) {
    throw std::invalid_argument("Variable with name: '" + variable->getName() + "' not found");
  }
  llvm_result = Builder->CreateLoad(loadedVar->getAllocatedType(), loadedVar, variable->getName().c_str());
}

void LLVM_Visitor::visitFunctionDeclaration(FunctionDeclaration* funcDeclExpr) {
  llvm::Type* returnType = getLLVMType(funcDeclExpr->getReturnType());
  llvm::FunctionType* funcType;

  funcType = llvm::FunctionType::get(returnType,{}, false);

  auto* function = llvm::Function::Create(
    funcType, 
    llvm::Function::ExternalLinkage,
    funcDeclExpr->getName(),
    TheModule.get()
  );                     

  auto* block = llvm::BasicBlock::Create(*TheContext, "entry", function);
  Builder->SetInsertPoint(block);

  funcDeclExpr->getBody()->accept(this);

  Builder->CreateRet(llvm_result);

  llvm::verifyFunction(*function);
}

void LLVM_Visitor::visitFunctionCall(FunctionCall* funcCallExpr) {
  llvm::Function* function = TheModule->getFunction(funcCallExpr->getName());

 /* if (!function) {
    throw std::invalid_argument("PANIC");
  }*/

  llvm_result = Builder->CreateCall(function, {});
}

void LLVM_Visitor::visitVariableAssignmentExpression(VariableAssignmentExpression *variable) {
  // get value to be stored
  BaseExpression* variableValue = variable->getValueExpression();
  variableValue->accept(this);
  std::string variableName = variable->getVariable()->getName();
  // create variable in memmory
  //llvm::Function *parentFunction = Builder->GetInsertBlock()->getParent();

  llvm::AllocaInst* varAllocation = (*Builder).CreateAlloca(llvm::Type::getInt64Ty(*TheContext), nullptr, variableName);//CreateEntryBlockAlloca(parentFunction, variableName);
  symbolTable[variableName] = varAllocation;

  //store value in variable
  Builder->CreateStore(llvm_result, varAllocation);

  if(variable->isVarMutable()){ mutableVars.insert(variableName); }
}

void LLVM_Visitor::visitVariableExpression(VariableExpression *variable) {
  llvm::AllocaInst* loadedVar = symbolTable[variable->getName()];
  if(!loadedVar) {
    throw std::invalid_argument("Variable with name: '" + variable->getName() + "' not found");
  }
  llvm_result = Builder->CreateLoad(loadedVar->getAllocatedType(), loadedVar, variable->getName().c_str());
}

llvm::Type* LLVM_Visitor::getLLVMType(std::string type) {
  if (type == "int") {
    return llvm::Type::getInt64Ty(*TheContext);
  } else {
    std::runtime_error("Unknown Type:" + type);
  }

  return llvm::Type::getVoidTy(*TheContext);
}
