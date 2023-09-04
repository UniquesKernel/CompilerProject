#pragma once

#include "Expression/expression.hpp"
#include "Expression/expressionType.hpp"
#include <vector>

struct ProductionRule {
  ExpressionType left;
  std::vector<ExpressionType> right;
};
