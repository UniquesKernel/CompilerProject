#pragma once

#include "Expression/expression.hpp"
#include "Token/token.hpp"
#include "Visitor/expressionVisitor.hpp"
#include <cwchar>
#include <memory>
#include <variant>

using ExpressionPtr = std::unique_ptr<const Expression>;

class BinaryExpression : public Expression {

private:
  const ExpressionPtr left;
  const ExpressionPtr right;
  const Token op;

public:
  BinaryExpression(const Token &op, ExpressionPtr left, ExpressionPtr right)
      : op(op), left(std::move(left)), right(std::move(right)) {}

  void accept(ExpressionVisitor &visitor) const override {
    visitor.visit(*this);
  }

  const Expression *getLeft() const { return left.get(); }
  const Expression *getRight() const { return right.get(); }
  Token getOp() const { return op; }
};
