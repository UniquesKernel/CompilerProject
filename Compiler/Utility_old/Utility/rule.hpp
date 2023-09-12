#pragma once

#include "Utility/symbol.hpp"
#include <vector>

struct Rule {
  Symbol lhs;
  std::vector<Symbol> rhs;

  Rule(Symbol lhs, std::vector<Symbol> rhs) : lhs(lhs), rhs(rhs){};

  // implement equals
  bool operator==(Rule other) {
    if (lhs == other.lhs && rhs == other.rhs) {
      return true;
    }
    return false;
  }
};
