#pragma once
#include <unordered_map>
#include <vector>
#include <stack>
#include <set>
#include <iostream>

#include "Lexer/lexer.hpp"
#include "Expression/expression.hpp"
#include "ProductionRule/productionRule.hpp"
#include "Expression/expressionType.hpp"
#include "LRItems/lritems.hpp"


class Parser {
// private:
public:
  Lexer lexer;

  std::unordered_map<ExpressionType, std::vector<ProductionRule>> grammar = {
    {EXPRESSION, 
      {
        {EXPRESSION, {BINARY_EXPRESSION}},
        {EXPRESSION, {TERMINAL_EXPRESSION}},
      }
    },
    {BINARY_EXPRESSION, 
      {
        {BINARY_EXPRESSION, {EXPRESSION, BINARY_OPERATOR_EXPRESSION, EXPRESSION}},
      }
    },
  };

  void construct_action_table();

public:
  std::unordered_map<std::set<LRItem>, int, std::hash<std::set<LRItem>>> item_set_mapping;
  std::set<LRItem> goTo_state(const std::set<LRItem>& items, const ExpressionType& symbol);
  std::set<LRItem> closure(const std::set<LRItem>& items);
  std::unordered_map<int, std::unordered_map<ExpressionType, std::string>> action_table;
  Parser(Lexer lexer): lexer(lexer) {
    construct_action_table();
  }

  void display_states();
  
};

