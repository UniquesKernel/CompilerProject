#include "Visitors/borrowChecker.hpp"
#include "Expressions/ReturnExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/ifExpression.hpp"
#include "Expressions/programExpression.hpp"
#include "Expressions/referenceAssignmentExpression.hpp"
#include "Visitors/baseVisitor.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>

void BorrowChecker::visitProgramExpression(ProgramExpression *program) {
  for (auto functionDeclaration : program->getFunctions()) {
    functionDeclaration->accept(this);
  }
}

void BorrowChecker::visitBinaryExpression(BinaryExpression *expression) {}

void BorrowChecker::visitVariableAssignmentExpression(
    VariableAssignmentExpression *variable) {}

void BorrowChecker::visitVariableExpression(VariableExpression *variable) {}

void BorrowChecker::visitReferenceAssignmentExpression(
    ReferenceAssignmentExpression *variable) {
  auto it = referenceMap.find(variable->getReferenceIdentifier());
  if (it == referenceMap.end()) {
    std::pair<std::string, bool> reference =
        std::make_pair(variable->getIdentifier(), variable->isVarMutable());
    std::vector<std::pair<std::string, bool>> referenceList;
    referenceList.push_back(reference);
    referenceMap.emplace(variable->getReferenceIdentifier(), referenceList);
  } else {
    it->second.emplace_back(variable->getIdentifier(),
                            variable->isVarMutable());
  }

  // Now check the state of the vector associated with the key
  std::vector<std::pair<std::string, bool>> &vec =
      referenceMap[variable->getReferenceIdentifier()]; // This is safe since we
                                                        // just ensured the key
                                                        // exists
  int mutableCount = 0;
  bool hasImmutable = false;
  for (const auto &pair : vec) {
    if (pair.second) {
      mutableCount++;
    } else {
      hasImmutable = true;
    }
  }

  if (mutableCount > 1) {
    throw std::invalid_argument(
        "Invalid argument: more than one mutable reference");
  } else if (mutableCount == 1 && hasImmutable) {
    throw std::invalid_argument(
        "Invalid argument: mixed mutable and immutable references");
  }
}

void BorrowChecker::visitTerminalExpression(TerminalExpression *terminal) {}

void BorrowChecker::visitBlockExpression(BlockExpression *block) {
  for (auto expr : block->getInstructions()) {
    expr->accept(this);
  }
}

void BorrowChecker::visitIfExpression(IfExpression *ifExpr) {
  ifExpr->getThenBlock()->accept(this);
  if (ifExpr->getElseBlock()) {
    ifExpr->getElseBlock()->accept(this);
  }
}

void BorrowChecker::visitFunctionDeclaration(
    FunctionDeclaration *funcDeclExpr) {
  funcDeclExpr->getBody()->accept(this);
}

void BorrowChecker::visitFunctionCall(FunctionCall *funcCallExpr) {}

void BorrowChecker::visitReturnExpression(ReturnExpression *returnExpr) {
  fi)
  returnExpr->getExpr()->accept(this);
}

void BorrowChecker::visitVariableReassignmentExpression(
    VariableReassignmentExpression *variable) {}
