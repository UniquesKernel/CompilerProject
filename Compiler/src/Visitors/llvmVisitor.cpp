#include "Visitors/llvmVisitor.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"

#include <iostream>

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

  std::cout << type << std::endl;

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

void LLVM_Visitor::visitIntegerExpression(TerminalExpression *integer) {
  llvm_result =
      llvm::ConstantInt::get(*TheContext, llvm::APInt(64, integer->getValue()));
}


void LLVM_Visitor::visitVariableAssignmentExpression(VariableAssignmentExpression *variable) {
  // get value to be stored
  BaseExpression* variableValue = variable->getValueExpression();
  variableValue->accept(this);
  std::string variableName = variable->getName();
  // create variable in memmory
  llvm::Function *parentFunction = Builder->GetInsertBlock()->getParent(); //scope?
  llvm::AllocaInst* varAllocation = CreateEntryBlockAlloca(parentFunction, variableName);
  symbolTable[variableName] = varAllocation;

  //store value in variable
  Builder->CreateStore(llvm_result, varAllocation);

  if(variable->isVarMutable()){ mutableVars.insert(variableName); }
}

void LLVM_Visitor::visitVariableExpression(VariableExpression *variable) {
  llvm::AllocaInst* loadedVar = symbolTable[variable->getName()];
  if(!loadedVar) {
    throw std::invalid_argument("Variable " + variable->getName() + " not found name");
  }
  llvm_result = Builder->CreateLoad(loadedVar->getAllocatedType(), loadedVar, variable->getName().c_str());
}
