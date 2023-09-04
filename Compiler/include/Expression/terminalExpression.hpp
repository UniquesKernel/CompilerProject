#pragma once

#include "Expression/expression.hpp"
#include "Token/token.hpp"
#include "Visitor/expressionVisitor.hpp"
#include <iostream>
#include <variant>

class TerminalExpression : public Expression {
private:
  std::variant<int> value;

public:
  TerminalExpression(const Token &token);

  void accept(ExpressionVisitor &visitor) const override {
    visitor.visit(*this);
  }

  auto getValue() const { return value; }
};
