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
  BaseExpression *condition;
  BlockExpression *thenBlock;
  BaseExpression *elseBlock;

public:
  IfExpression(BaseExpression *condition, BlockExpression *thenBlock,
               BaseExpression *elseBlock)
      : condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {
  }

  BaseExpression *getCondition() { return condition; }
  BlockExpression *getThenBlock() { return thenBlock; }
  BaseExpression *getElseBlock() { return elseBlock; }

  void accept(BaseVisitor *visitor) override {
    visitor->visitIfExpression(this);
  }
};
