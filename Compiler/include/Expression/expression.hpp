#pragma once

class ExpressionVisitor;

class Expression {
public:
  virtual void accept(ExpressionVisitor &visitor) const = 0;
};
