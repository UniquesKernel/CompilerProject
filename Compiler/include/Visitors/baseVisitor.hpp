#pragma once

class BinaryExpression;
class TerminalExpression;
class VariableExpression;
class VariableAssignmentExpression;

class BaseVisitor {
public:
  virtual void visitBinaryExpression(BinaryExpression *expression) = 0;
  virtual void visitIntegerExpression(TerminalExpression *integer) = 0;
  virtual void visitVariableAssignmentExpression(VariableAssignmentExpression *variable) = 0;
  virtual void visitVariableExpression(VariableExpression *variable) = 0;
};
