#pragma once

#include "Utility/LRItem.hpp"
#include "Utility/rule.hpp"
#include "Utility/symbol.hpp"
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

class Grammar {
private:
  std::unordered_map<Symbol, std::vector<Rule>> rules = {};
  std::set<Symbol> terminals = {};
  std::set<Symbol> nonTerminals = {};
  Symbol start = Symbol::START;
  std::map<Symbol, std::set<Symbol>> firstSets = {};
  std::map<Symbol, std::set<Symbol>> followSets = {};

  void findTerminals();
  void findNonTerminals();
  void computeFirstSets();
  void computeFollowSets();
  std::set<Symbol> computeFirst(std::vector<Symbol> symbol, uint symbolIndex);

public:
  Grammar(std::unordered_map<Symbol, std::vector<Rule>> rules);
  std::set<Symbol> getTerminals() const { return terminals; };
  std::set<Symbol> getNonTerminals() const { return nonTerminals; };
  std::map<Symbol, std::set<Symbol>> getFirstSets() const { return firstSets; };
  std::map<Symbol, std::set<Symbol>> getFollowSets() const {
    return followSets;
  };
  void calculateStates(const LRItem &start);
  std::set<LRItem> closure(const LRItem &items);

  std::set<std::set<LRItem>> states;
};
