#pragma once

#include "Expression/binaryExpression.hpp"
#include "Expression/terminalExpression.hpp"
#include "expressionVisitor.hpp"
#include <iostream>
#include <stdexcept>
#include <variant>

class EvaluatorVisitor : public ExpressionVisitor {
private:
  std::variant<int> result;

public:
  EvaluatorVisitor() {}
  void visit(const TerminalExpression &terminalExpression) override;
  void visit(const BinaryExpression &binaryExpression) override;

  template <typename T> T getResult() const;
};

template <typename T> T EvaluatorVisitor::getResult() const {
  if (std::holds_alternative<T>(result)) {
    return std::get<T>(result);
  } else {
    throw std::runtime_error("Result is not of type " +
                             std::string(typeid(T).name()));
  }
}
