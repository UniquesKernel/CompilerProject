#include "Expressions/baseExpression.hpp"
#include "Visitors/baseVisitor.hpp"
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class typeCheckingVisitor : public BaseVisitor {
private:
  std::string type;

public:
  std::stack<std::unordered_map<std::string, std::string>> typeTable;
  std::unordered_map<std::string, std::vector<std::string>> functionArgTypes;
  std::unordered_map<std::string, std::string> functionTypes;


  void visitTerminalExpression(TerminalExpression *terminal) override;
  void visitBinaryExpression(BinaryExpression *expression) override;
  void visitVariableAssignmentExpression(
      VariableAssignmentExpression *variable) override;
  void visitVariableExpression(VariableExpression *variable) override;
  void visitBlockExpression(BlockExpression *block) override;
  void visitReturnExpression(ReturnExpression *returnExpr) override;
  void visitIfExpression(IfExpression *IfExpr) override;
  void visitFunctionDeclaration(FunctionDeclaration *FuncDeclExpr) override;
  void visitFunctionCall(FunctionCall *FuncCallExpr) override;
  void visitProgramExpression(ProgramExpression *funcCallExpr) override;
  void visitVariableReassignmentExpression(
      VariableReassignmentExpression *variable) override;
};