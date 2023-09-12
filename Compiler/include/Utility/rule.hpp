#pragma once

#include "Utility/symbol.hpp"

#include <vector>

class Rule {
private:
  const Symbol lhs;
  const std::vector<Symbol> rhs;

public:
  Rule(const Symbol lhs, const std::vector<Symbol> rhs) : lhs(lhs), rhs(rhs) {}
  Symbol getLhs() const { return lhs; }
  std::vector<Symbol> getRhs() const { return rhs; }

  bool operator==(const Rule &other) const {
    return lhs == other.lhs && rhs == other.rhs;
  }
};
