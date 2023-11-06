#pragma once

#include "Visitors/baseVisitor.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class BorrowChecker : public BaseVisitor {
public:
  BorrowChecker(){};
  void visitBinaryExpression(BinaryExpression *expression) override;
  void visitVariableAssignmentExpression(
      VariableAssignmentExpression *variable) override;
  void visitVariableExpression(VariableExpression *variable) override;
  void visitReferenceAssignmentExpression(
      ReferenceAssignmentExpression *variable) override;
  void visitTerminalExpression(TerminalExpression *terminal) override;
  void visitBlockExpression(BlockExpression *block) override;
  void visitIfExpression(IfExpression *ifExpr) override;
  void visitFunctionDeclaration(FunctionDeclaration *funcDeclExpr) override;
  void visitFunctionCall(FunctionCall *funcCallExpr) override;
  void visitReturnExpression(ReturnExpression *returnExpr) override;
  void visitProgramExpression(ProgramExpression *funcCallExpr) override;
  void visitVariableReassignmentExpression(
      VariableReassignmentExpression *variable) override;

private:
  std::unordered_map<std::string, std::vector<std::pair<std::string, bool>>>
      referenceMap;
};
