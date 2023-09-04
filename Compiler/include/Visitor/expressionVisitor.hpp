#pragma once

class TerminalExpression;
class BinaryExpression;

class ExpressionVisitor {

public:
  virtual void visit(const TerminalExpression &terminalExpression) = 0;
  virtual void visit(const BinaryExpression &binaryExpression) = 0;
};
