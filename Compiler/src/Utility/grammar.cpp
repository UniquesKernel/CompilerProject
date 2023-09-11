#include "Utility/grammar.hpp"
#include "Utility/LRItem.hpp"
#include "Utility/symbol.hpp"
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <unordered_map>

Grammar::Grammar(std::unordered_map<Symbol, std::vector<Rule>> rules)
    : rules(rules) {

  rules[Symbol::START].push_back(Rule(Symbol::START, {Symbol::EXPRESSION}));

  LRItem start = LRItem(rules[Symbol::START][0], 0);

  findNonTerminals();
  findTerminals();
  computeFirstSets();
  computeFollowSets();
  calculateStates(start);
}
void Grammar::findNonTerminals() {
  for (const auto &[symbol, rule] : rules) {
    nonTerminals.insert(symbol);
  }
}

void Grammar::findTerminals() {
  for (const auto &[symbol, rule] : rules) {
    for (const Rule &r : rule) {
      for (const Symbol &s : r.rhs) {
        if (!nonTerminals.contains(s)) {
          terminals.insert(s);
        }
      }
    }
  }
}

void Grammar::computeFirstSets() {
  for (const Symbol &symbol : terminals) {
    firstSets[symbol].insert(symbol);
  }

  for (const auto &symbol : nonTerminals) {
    firstSets[symbol] = std::set<Symbol>();
  }

  while (true) {
    bool changed = false;

    for (const Symbol &symbol : nonTerminals) {
      std::set<Symbol> firstSet = std::set<Symbol>();
      std::vector<Rule> relevantRules = rules[symbol];

      for (const Rule &rule : relevantRules) {
        std::set<Symbol> first = computeFirst(rule.rhs, 0);
        firstSet.insert(first.begin(), first.end());
      }

      if (firstSets[symbol] != firstSet) {
        changed = true;
        firstSets[symbol].insert(firstSet.begin(), firstSet.end());
      }
    }

    if (!changed) {
      break;
    }
  }
}

std::set<Symbol> Grammar::computeFirst(std::vector<Symbol> ruleRhs,
                                       uint symbolIndex) {
  std::set<Symbol> first = std::set<Symbol>();

  if (symbolIndex >= ruleRhs.size()) {
    first.insert(Symbol::EPSILON);
    return first;
  }

  Symbol currentSymbol = ruleRhs[symbolIndex];

  if (terminals.contains(currentSymbol) || currentSymbol == Symbol::EPSILON) {
    first.insert(currentSymbol);
    return first;
  }

  if (nonTerminals.contains(currentSymbol)) {
    first.insert(firstSets[currentSymbol].begin(),
                 firstSets[currentSymbol].end());
  }

  if (first.contains(Symbol::EPSILON) && symbolIndex != (ruleRhs.size() - 1)) {
    first.erase(Symbol::EPSILON);
    first.merge(computeFirst(ruleRhs, symbolIndex + 1));
  }

  return first;
}

void Grammar::computeFollowSets() {
  for (const auto &symbol : nonTerminals) {
    followSets[symbol] = std::set<Symbol>();
  }

  followSets[Symbol::START].insert(Symbol::END_OF_FILE);

  while (true) {
    bool changed = false;
    for (const Symbol &symbol : nonTerminals) {
      for (const auto &[s, rulesVector] : rules) {
        for (const Rule rule : rulesVector) {
          for (uint i = 0; i < rule.rhs.size(); i++) {
            if (rule.rhs[i] == symbol) {
              std::set<Symbol> first;
              size_t oldSize = followSets[symbol].size();
              if (i == rule.rhs.size() - 1) {
                first = followSets[rule.lhs];
              } else {
                first = computeFirst(rule.rhs, i + 1);
                if (first.contains(Symbol::EPSILON)) {
                  first.erase(Symbol::EPSILON);
                  first.insert(followSets[rule.lhs].begin(),
                               followSets[rule.lhs].end());
                }
              }

              followSets[symbol].insert(first.begin(), first.end());
              if (followSets[symbol].size() != oldSize) {
                changed = true;
              }
            }
          }
        }
      }
    }
    if (!changed) {
      break;
    }
  }
}

std::set<LRItem> Grammar::closure(const LRItem &input_item) {
  std::set<LRItem> closure_items;
  closure_items.insert(input_item);
  bool items_added = true;
  while (items_added) {
    items_added = false;
    std::set<LRItem> new_items;
    for (LRItem item : closure_items) {
      if (item.dotPosition < item.productionRule.rhs.size()) {
        Symbol symbol = item.productionRule.rhs[item.dotPosition];
        if (rules.find(symbol) != rules.end()) {
          for (const Rule &productionRule : rules[symbol]) {
            LRItem new_item = LRItem(productionRule, 0);
            new_items.insert(new_item);
          }
        }
      }
    }
    for (LRItem item : new_items) {
      if (closure_items.find(item) == closure_items.end()) {
        closure_items.insert(item);
        items_added = true;
      }
    }
  }
  return closure_items;
}

void Grammar::calculateStates(const LRItem &start) {

  states.insert(closure(start));
  bool state_added = true;

  while (state_added) {
    state_added = false;
    for (std::set<LRItem> state : states) {
      for (LRItem item : state) {
        if (item.dotPosition < item.productionRule.rhs.size()) {
          LRItem new_item = LRItem(item.productionRule, item.dotPosition + 1);
          std::set<LRItem> new_state = closure(new_item);
          if (states.find(new_state) == states.end()) {
            states.insert(new_state);
            state_added = true;
          }
        }
      }
    }
  }
}
