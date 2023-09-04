#pragma once

// 1 + 1
// TokenType::INTEGER
// tokenType::PLUS
// TokenType::INTEGER

struct ProductionRule {
  Expression left
  std::vector<Expressions> right

  ProductionRule(Expression left, std::vector<Expressions> right)
    : left(left), right(right) {}
};
