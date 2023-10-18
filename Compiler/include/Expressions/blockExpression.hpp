#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <vector>

class BlockExpression : public BaseExpression {
private:
  std::vector<BaseExpression *> instructions;

public:
  BlockExpression(std::vector<BaseExpression *> instructions)
      : instructions(instructions) {}
  BlockExpression() {}

  std::vector<BaseExpression *> getInstructions() { return instructions; }
  void accept(BaseVisitor *visitor) override {
    visitor->visitBlockExpression(this);
  }
};
