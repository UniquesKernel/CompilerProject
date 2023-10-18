#pragma once

#include "Expressions/baseExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Visitors/baseVisitor.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <stdexcept>

class IfExpression : public BaseExpression {
private:
  TerminalExpression *condition;
  BlockExpression *thenBlock;
  BaseExpression *elseBlock;

public:
  IfExpression(TerminalExpression *condition, BlockExpression *thenBlock,
               BaseExpression *elseBlock)
      : condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {

    if (condition->getType() != "boolean") {
      std::invalid_argument("Expected a boolean expression");
    }
  }

  TerminalExpression *getCondition() { return condition; }
  BlockExpression *getThenBlock() { return thenBlock; }
  BaseExpression *getElseBlock() { return elseBlock; }

  void accept(BaseVisitor *visitor) override {
    visitor->visitIfExpression(this);
  }
};
