#pragma once

#include "Expressions/baseExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Visitors/baseVisitor.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>

class IfExpression : public BaseExpression {
private:
  BaseExpression *condition;
  BaseExpression *thenBlock;
  BaseExpression *elseBlock;

public:
  IfExpression(BaseExpression *condition, BaseExpression *thenBlock, BaseExpression *elseBlock)
      : condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {
  
    std::cout << dynamic_cast<TerminalExpression*>(condition)->getType() << std::endl;

    if (dynamic_cast<TerminalExpression*>(condition)->getType() != TerminalType::BOOLEAN) {
      throw std::runtime_error("If condition must be a boolean expression");
    }

    if (!(dynamic_cast<BlockExpression*>(thenBlock))) {
      throw std::runtime_error("If is expecting { } expression."); 
    }

    if (!(dynamic_cast<BlockExpression*>(elseBlock) || dynamic_cast<IfExpression*>(elseBlock)) && elseBlock != nullptr) {
      throw std::runtime_error("else is expecting either {} or if ().");
    }
  }

  BaseExpression *getCondition() { return condition; }
  BaseExpression *getThenBlock() { return thenBlock; }
  BaseExpression *getElseBlock() { return elseBlock; }

  void accept(LLVM_Visitor *visitor) override {
    visitor->visitIfExpression(this);
  }
};
