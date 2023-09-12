#include "Utility/grammar.hpp"
#include "Utility/rule.hpp"
#include "Utility/symbol.hpp"
#include <ranges>
#include <vector>

Grammar::Grammar(std::vector<Rule> rules) : rules(rules){

  startSymbol = rules[0].getLhs();
  this->rules.push_back(Rule(Symbol::START, {startSymbol}));

  computeNonTerminals();
  computeTerminals();
  computeFirstSets();
  computeFollowSets();
}

void Grammar::computeNonTerminals() {
  for (const Rule &rule : rules) {
    nonTerminals.insert(rule.getLhs());
  }
}

void Grammar::computeTerminals() {
  for (const Rule &rule : rules) {
    for (const Symbol &symbol : rule.getRhs()) {
      if (!isNonTerminal(symbol)) {
        terminals.insert(symbol);
      }
    }
  }
}

bool Grammar::isNonTerminal(const Symbol &symbol) const {
  return nonTerminals.contains(symbol);
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
      auto relevantRules = rules | std::views::filter(
                                    [symbol](const Rule &rule) {
                                      return rule.getLhs() == symbol;
                                    });

      for (const Rule &rule : relevantRules) {
        std::set<Symbol> first = computeFirstSet(rule.getRhs(), 0);
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

std::set<Symbol> Grammar::computeFirstSet(std::vector<Symbol> ruleRhs,
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
    first.merge(computeFirstSet(ruleRhs, symbolIndex + 1));
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

    for (const Symbol& symbol : nonTerminals) {
      for (const Rule& rule : rules) {
        for (uint i = 0; i < rule.getRhs().size(); i++) {
          if (rule.getRhs()[i] == symbol) {
            std::set<Symbol> first;
            size_t oldSize = followSets[symbol].size();

            if (i == rule.getRhs().size() - 1) {
              first = followSets[rule.getLhs()];
            } else {
              first = computeFirstSet(rule.getRhs(), i + 1);
              if (first.contains(Symbol::EPSILON)) {
                first.erase(Symbol::EPSILON);
                first.insert(followSets[rule.getLhs()].begin(),
                             followSets[rule.getLhs()].end());
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
    if (!changed) {
      break;
    }
  }
}


