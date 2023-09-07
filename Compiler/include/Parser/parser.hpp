#pragma once
#include <unordered_map>
#include <vector>
#include <stack>
#include <set>
#include <iostream>

#include "Lexer/lexer.hpp"
#include "Expression/expression.hpp"
#include "ProductionRule/productionRule.hpp"
#include "symbols.hpp"
#include "LRItems/lritems.hpp"


// class Parser {
// // private:
// public:
//   Lexer lexer;

//   std::unordered_map<ExpressionType, std::vector<ProductionRule>> grammar = {
//     {EXPRESSION, 
//       {
//         {EXPRESSION, {BINARY_EXPRESSION}},
//         {EXPRESSION, {TERMINAL_EXPRESSION}},
//       }
//     },
//     {BINARY_EXPRESSION, 
//       {
//         {BINARY_EXPRESSION, {EXPRESSION, BINARY_OPERATOR_EXPRESSION, EXPRESSION}},
//       }
//     },
//   };

//   void construct_action_table();

// public:
//   std::unordered_map<std::set<LRItem>, int, std::hash<std::set<LRItem>>> item_set_mapping;
//   std::set<LRItem> goTo_state(const std::set<LRItem>& items, const ExpressionType& symbol);
//   std::set<LRItem> closure(const std::set<LRItem>& items);
//   std::unordered_map<int, std::unordered_map<ExpressionType, std::string>> action_table;
//   Parser(Lexer lexer): lexer(lexer) {
//     construct_action_table();
//   }

//   void display_states();
  
// };

class grammar_handler {
  private:
    std::unordered_map<Symbol, std::vector<ProductionRule>> grammar = {
      {EXPRESSION, 
      {
        {EXPRESSION, {INTEGER}},
        {EXPRESSION, {BINARY_EXPRESSION}},
      }
    },
    {BINARY_EXPRESSION, 
      {
        {BINARY_EXPRESSION, {EXPRESSION, PLUS, EXPRESSION}},
      }
    },
  };

    std::unordered_map<Symbol, std::set<Symbol>> first;
    std::unordered_map<Symbol, std::set<LRItem>> states;

    // Expression lists
    std::set<Symbol> terminalExpression;
    std::set<Symbol> nonTerminalExpression;


  public:

    void populateExpressionLists();
    // void populateMaps();
    void calculateStates();
    std::set<LRItem> closure(const std::set<LRItem>& items);

};