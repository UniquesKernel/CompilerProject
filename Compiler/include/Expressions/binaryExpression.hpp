#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

class BinaryExpression : public BaseExpression {
private:
  BaseExpression *lhs;
  BaseExpression *rhs;
  char type;

public:
  BinaryExpression(BaseExpression *lhs, char type, BaseExpression *rhs)
      : lhs(lhs), rhs(rhs), type(type) {}
  BaseExpression *getLHS() { return lhs; }
  BaseExpression *getRHS() { return rhs; }
  char getType() { return type; }
  void accept(LLVM_Visitor *visitor) override;
};
