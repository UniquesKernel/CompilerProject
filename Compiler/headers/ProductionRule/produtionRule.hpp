#pragma once

#include "Expression/expressionType.hpp"

// 1 + 1
// TokenType::INTEGER
// tokenType::PLUS
// TokenType::INTEGER

struct ProductionRule {
  ExpressionType left
  std::vector<ExpressionType> right

  ProductionRule(ExpressionType left, std::vector<ExpressionType> right)
    : left(left), right(right) {}

};
