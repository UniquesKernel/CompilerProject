#include "Visitors/borrowChecker.hpp"
#include "Expressions/ReturnExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/ifExpression.hpp"
#include "Expressions/programExpression.hpp"
#include "Expressions/referenceAssignmentExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"
#include "Visitors/baseVisitor.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>

void BorrowChecker::visitProgramExpression(ProgramExpression *program) {
  for (auto functionDeclaration : program->getFunctions()) {
    functionDeclaration->accept(this);
  }
}

void BorrowChecker::visitBinaryExpression(BinaryExpression *expression) {
  expression->getLHS()->accept(this);
  expression->getRHS()->accept(this);
}

void BorrowChecker::visitVariableAssignmentExpression(
    VariableAssignmentExpression *variable) {
  VariableInfo variableInfo = VariableInfo(variable->getVariable()->getName());

  if (variable->getVariable()->getIsReference()) {
    variableInfo.setReference();
  }

  if (variable->isVarMutable()) {
    variableInfo.setMutable();
  }

  symbolTable.top().push_back(variableInfo);
}

void BorrowChecker::visitVariableExpression(VariableExpression *variable) {
  auto tempStack = symbolTable;

  while (!tempStack.empty()) {
    for (auto variableInfo : tempStack.top()) {
      if (variableInfo.getName() == variable->getName()) {
        return;
      }
    }
    tempStack.pop();
  }

  throw std::invalid_argument("Invalid argument: " + variable->getName() +
                              " not accessible in scope");
}

void BorrowChecker::visitReferenceAssignmentExpression(
    ReferenceAssignmentExpression *variable) {
  auto tempStack = symbolTable;
  bool found = false;
  while (!tempStack.empty()) {
    for (auto variableInfo : tempStack.top()) {
      if (variableInfo.getName() == variable->getReferenceIdentifier()) {
        found = true;
        break;
      }
    }
    tempStack.pop();
  }

  if (!found) {
    throw std::invalid_argument(
        "Invalid argument: variable not accessible in scope");
  }

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

void BorrowChecker::visitTerminalExpression(TerminalExpression *terminal) {
  // Do nothing
}

void BorrowChecker::visitBlockExpression(BlockExpression *block) {
  symbolTable.push(std::vector<VariableInfo>());
  for (auto expr : block->getInstructions()) {
    expr->accept(this);
  }
  symbolTable.pop();
}

void BorrowChecker::visitIfExpression(IfExpression *ifExpr) {
  ifExpr->getThenBlock()->accept(this);
  if (ifExpr->getElseBlock() != nullptr) {
    ifExpr->getElseBlock()->accept(this);
  }
}

void BorrowChecker::visitFunctionDeclaration(
    FunctionDeclaration *funcDeclExpr) {
  symbolTable.push(std::vector<VariableInfo>());
  for (auto param : funcDeclExpr->getArgs()) {
    VariableInfo variableInfo = VariableInfo(param.second);
    variableInfo.setParam();
    symbolTable.top().push_back(variableInfo);
  }
  funcDeclExpr->getBody()->accept(this);
  symbolTable.pop();
}

void BorrowChecker::visitFunctionCall(FunctionCall *funcCallExpr) {
  for (auto arg : funcCallExpr->getArgs()) {
    arg->accept(this);
  }

  for (auto arg : funcCallExpr->getArgs()) {
    if (auto varExpr = dynamic_cast<VariableExpression *>(arg)) {
      if (varExpr->getIsReference()) {
        continue;
      }
      std::string varName = varExpr->getName();
      std::stack<std::vector<VariableInfo>> tempStack;
      bool found = false;
      bool shouldErase = true;

      while (!symbolTable.empty() && !found) {
        std::vector<VariableInfo> topVector = symbolTable.top();
        VariableInfo topVariable = VariableInfo("");
        int index = 0;
        for (auto variableInfo : topVector) {
          if (variableInfo.getName() == varName) {
            found = true;
            topVariable = variableInfo;
            if (variableInfo.isParam()) {
              shouldErase = false;
            } else {
              shouldErase = true;
            }
            if (found) {
              break; // Break out of the loop if you've found and potentially
                     // erased the variable
            }
          } else {
            index++;
          }
        }

        if (shouldErase && !topVector.empty()) {
          topVector.erase(topVector.begin() + index);
        }

        if (!topVector.empty()) {
          tempStack.push(topVector);
        } else {
          tempStack.push(std::vector<VariableInfo>());
        }

        symbolTable.pop();
      }

      while (!tempStack.empty()) {
        symbolTable.push(tempStack.top());
        tempStack.pop();
      }
    }
  }
}

void BorrowChecker::visitReturnExpression(ReturnExpression *returnExpr) {
  returnExpr->getExpr()->accept(this);
}

void BorrowChecker::visitVariableReassignmentExpression(
    VariableReassignmentExpression *variable) {
  bool found = false;

  std::vector<std::string> keys_with_value;

  auto tempStack = symbolTable;
  while (!tempStack.empty()) {
    if (found) {
      break;
    }
    for (auto variableInfo : tempStack.top()) {
      if (variableInfo.getName() == variable->getVariable()->getName()) {
        found = true;
        break;
      }
    }
    tempStack.pop();
  }

  if (!found) {
    throw std::invalid_argument(
        "Invalid argument: " + variable->getVariable()->getName() +
        " is not accessible in scope");
  }
}
