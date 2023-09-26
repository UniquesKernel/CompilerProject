#include "Visitors/llvmVisitor.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/ReturnExpression.hpp"
#include "Expressions/ifExpression.hpp"
#include "Visitors/baseVisitor.hpp"
#include <iostream>

void LLVM_Visitor::visitBinaryExpression(BinaryExpression *expression) {
  expression->getLHS()->accept(this);
  llvm::Value *L = llvm_result;
  expression->getRHS()->accept(this);
  llvm::Value *R = llvm_result;
  char type = expression->getType();

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
  
  if (block->getInstructions().empty()) {
    return;
  }

  for (auto& expr : block->getInstructions()) {
    if (dynamic_cast<ReturnExpression*>(expr) != nullptr) {
      expr->accept(this);
      break;
    }
    expr->accept(this);
  }
}

void LLVM_Visitor::visitReturnExpression(ReturnExpression *returnExpr) {
  returnExpr->getExpr()->accept(this);
}

void LLVM_Visitor::visitIfExpression(IfExpression *ifExpression) {
  TerminalExpression* condition = (TerminalExpression*) ifExpression->getCondition();

  if (condition->getBoolValue()) {
    ifExpression->getThenBlock()->accept(this);
  } else if (ifExpression->getElseBlock() != nullptr) {
    ifExpression->getElseBlock()->accept(this);
  }
}
