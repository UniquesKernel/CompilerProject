#include "Visitor/evaluatorVisitor.hpp"
#include "Visitor/expressionVisitor.hpp"
#include <limits>

void EvaluatorVisitor::visit(const TerminalExpression &terminalExpression) {
  result = terminalExpression.getValue();
}

void EvaluatorVisitor::visit(const BinaryExpression &binaryExpression) {
  binaryExpression.getLeft()->accept(*this);
  auto left = getResult<int>();
  binaryExpression.getRight()->accept(*this);
  auto right = getResult<int>();

  switch (binaryExpression.getOp().getType()) {
  case TokenType::PLUS:
    if ((left > 0) && (right > std::numeric_limits<int>::max() - left)) {
      throw std::overflow_error("Integer overflow detected");
    }

    if ((left < 0) && (right < std::numeric_limits<int>::min() - left)) {
      throw std::underflow_error("Integer underflow detected");
    }

    result = left + right;

    break;
  default:
    throw std::runtime_error("Unknown operator");
  }
}
