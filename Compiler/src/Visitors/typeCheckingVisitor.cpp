#include "Visitors/typeCheckingVisitor.hpp"

#include "Expressions/ReturnExpression.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/ifExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"

void typeCheckingVisitor::visitTerminalExpression(
    TerminalExpression *terminal) {
  type = terminal->getType();
}

void typeCheckingVisitor::visitBinaryExpression(BinaryExpression *expression) {
  expression->getLHS()->accept(this);
  std::string lhsType = type;
  expression->getRHS()->accept(this);
  std::string rhsType = type;

  if (lhsType == rhsType) {
    type = lhsType;
  } else {
    throw std::invalid_argument("Binary operation with mismatching types: " +
                                lhsType + " and " + rhsType + "\n");
  }
}

void typeCheckingVisitor::visitVariableAssignmentExpression(
    VariableAssignmentExpression *variable) {
  variable->getVariable()->accept(this);
  if (variable->getType() != type) {
    throw std::invalid_argument(
        "variable assignment operation with mismatching types: " +
        variable->getType() + " and " + type + "\n");
  } else {
    typeTable.insert({variable->getVariable()->getName(), variable->getType()});
  }
}

void typeCheckingVisitor::visitVariableExpression(
    VariableExpression *variable) {
  type = typeTable.at(variable->getName());
}

void typeCheckingVisitor::visitBlockExpression(BlockExpression *block) {}

void typeCheckingVisitor::visitReturnExpression(ReturnExpression *returnExpr) {}

void typeCheckingVisitor::visitIfExpression(IfExpression *IfExpr) {}

void typeCheckingVisitor::visitFunctionDeclaration(
    FunctionDeclaration *FuncDeclExpr) {}

void typeCheckingVisitor::visitFunctionCall(FunctionCall *FuncCallExpr) {}