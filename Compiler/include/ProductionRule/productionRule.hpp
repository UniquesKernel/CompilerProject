#pragma once

#include "Expression/expression.hpp"
#include "symbols.hpp"
#include <vector>

struct ProductionRule {
  Symbol left;
  std::vector<Symbol> right;
};
