#pragma once

#include "Utility/rule.hpp"
#include "Utility/symbol.hpp"
#include <iostream>
#include <set>

class LRItem {
private:
public:
  bool operator<(const LRItem &rhs) const {
    if (productionRule.lhs != rhs.productionRule.lhs) {
      return productionRule.lhs < rhs.productionRule.lhs;
    } else if (dotPosition != rhs.dotPosition) {
      return dotPosition < rhs.dotPosition;
    } else if (productionRule.rhs.size() != rhs.productionRule.rhs.size()) {
      return productionRule.rhs.size() < rhs.productionRule.rhs.size();
    } else {
      for (int i = 0; i < productionRule.rhs.size(); i++) {
        if (productionRule.rhs[i] < rhs.productionRule.rhs[i]) {
          return true;
        }
      }
      return false;
    }
  }

  bool operator==(const LRItem &rhs) const {
    return dotPosition == rhs.dotPosition &&
           productionRule.lhs == rhs.productionRule.lhs &&
           productionRule.rhs == rhs.productionRule.rhs;
  }

  void print() {
    std::cout << productionRule.lhs << " -> ";
    for (int i = 0; i < productionRule.rhs.size(); i++) {
      if (i == dotPosition)
        std::cout << ". ";
      std::cout << productionRule.rhs[i] << " ";
    }
    std::cout << "\n";
  }

  Rule productionRule;
  int dotPosition;

  LRItem(Rule rule, int dotPosition)
      : productionRule(rule), dotPosition(dotPosition) {}
};

namespace std {
template <> struct hash<LRItem> {
  std::size_t operator()(const LRItem &item) const {
    std::size_t h1 = std::hash<Symbol>{}(item.productionRule.lhs);
    std::size_t h2 = std::hash<int>{}(item.dotPosition);
    return h1 * (h2 + 1);
  }
};

// create a hash for std::set<LRItem>
template <> struct hash<std::set<LRItem>> {
  std::size_t operator()(const std::set<LRItem> &items) const {
    std::size_t h = 0;
    for (const LRItem &item : items) {
      h ^= std::hash<LRItem>{}(item);
    }
    return h;
  }
};
} // namespace std
