#pragma once

class BinaryExpression;
class TerminalExpression;
class VariableExpression;
class VariableAssignmentExpression;
class BlockExpression;
class ReturnExpression;
class IfExpression;
class FunctionDeclaration;
class FunctionCall;
class ProgramExpression;
class VariableReassignmentExpression;
class ReferenceAssignmentExpression;

class BaseVisitor {
public:
  virtual void visitBinaryExpression(BinaryExpression *expression) = 0;
  virtual void
  visitVariableAssignmentExpression(VariableAssignmentExpression *variable) = 0;
  virtual void visitVariableExpression(VariableExpression *variable) = 0;
  virtual void visitReferenceAssignmentExpression(
      ReferenceAssignmentExpression *variable) = 0;
  virtual void visitTerminalExpression(TerminalExpression *terminal) = 0;
  virtual void visitBlockExpression(BlockExpression *block) = 0;
  virtual void visitReturnExpression(ReturnExpression *returnExpr) = 0;
  virtual void visitIfExpression(IfExpression *IfExpr) = 0;
  virtual void visitFunctionDeclaration(FunctionDeclaration *funcDeclExpr) = 0;
  virtual void visitFunctionCall(FunctionCall *funcCallExpr) = 0;
  virtual void visitProgramExpression(ProgramExpression *funcCallExpr) = 0;
  virtual void visitVariableReassignmentExpression(
      VariableReassignmentExpression *variable) = 0;
};
