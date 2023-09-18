#pragma once

class BinaryExpression;
class TerminalExpression;

class BaseVisitor {
public:
  virtual void visitBinaryExpression(BinaryExpression *expression) = 0;

  virtual void visitIntegerExpression(TerminalExpression *integer) = 0;
};