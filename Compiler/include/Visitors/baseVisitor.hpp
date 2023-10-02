#pragma once

class BinaryExpression;
class TerminalExpression;
class VariableExpression;
class VariableAssignmentExpression;
class BlockExpression;
class ReturnExpression;
class IfExpression;

class BaseVisitor {
public:
  virtual void visitBinaryExpression(BinaryExpression *expression) = 0;
  virtual void visitVariableAssignmentExpression(VariableAssignmentExpression *variable) = 0;
  virtual void visitVariableExpression(VariableExpression *variable) = 0;
  virtual void visitTerminalExpression(TerminalExpression *terminal) = 0;
  virtual void visitBlockExpression(BlockExpression *block) = 0;
  virtual void visitReturnExpression(ReturnExpression *returnExpr) = 0;
  virtual void visitIfExpression(IfExpression *IfExpr) = 0;
};
