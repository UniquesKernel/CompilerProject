#pragma once

#include "Utility/rule.hpp"
#include "Utility/symbol.hpp"
#include <set>
#include <vector>
#include <map>

class Grammar {
private:
  std::vector<Rule> rules;
  std::set<Symbol> terminals;
  std::set<Symbol> nonTerminals;
  Symbol startSymbol;
  std::map<Symbol, std::set<Symbol>> firstSets;
  std::map<Symbol, std::set<Symbol>> followSets;

  void computeTerminals();
  void computeNonTerminals();
  void computeFirstSets();
  void computeFollowSets();
  
  std::set<Symbol> computeFirstSet(std::vector<Symbol> rhs, uint symbolIndex);


public:
  Grammar(std::vector<Rule> rules);

  bool isNonTerminal(const Symbol &symbol) const;
  std::set<Symbol> getTerminals() const { return terminals; }
  std::set<Symbol> getNonTerminals() const { return nonTerminals; }
  std::map<Symbol, std::set<Symbol>> getFirstSets() const { return firstSets; }
  std::map<Symbol, std::set<Symbol>> getFollowSets() const { return followSets; }

};
