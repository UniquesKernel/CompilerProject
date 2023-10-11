#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <memory>

#include <iostream>

class BinaryExpression : public BaseExpression {
private:
  std::unique_ptr<BaseExpression> lhs;
  std::unique_ptr<BaseExpression> rhs;
  char op;

public:
  BinaryExpression(std::unique_ptr<BaseExpression> lhs, char op,
                   std::unique_ptr<BaseExpression> rhs)
      : lhs(std::move(lhs)), op(op), rhs(std::move(rhs)) {}
  BaseExpression *getLHS() { return lhs.get(); }
  BaseExpression *getRHS() { return rhs.get(); }
  char getOPType() { return op; }
  void accept(BaseVisitor *visitor) override;

  static BinaryExpression *createBinaryExpression(BaseExpression *lhs_raw,
                                                  char op,
                                                  BaseExpression *rhs_raw);
};
