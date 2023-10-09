#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <vector>

class BlockExpression : public BaseExpression {
public:
  std::vector<BaseExpression *> innerExpressions;

  BlockExpression(std::vector<BaseExpression *> inner)
      : innerExpressions(inner) {}

  void accept(LLVM_Visitor *visitor) { visitor->visitBlockExpression(this); };

  std::vector<BaseExpression *> getInnerExpressions() {
    return innerExpressions;
  }
};
