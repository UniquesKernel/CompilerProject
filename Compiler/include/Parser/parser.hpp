#pragma once

#include "Lexer/lexer.hpp"
#include "Expression/expression.hpp"
#include "ProductionRule/productionRule.hpp"
#include "Expression/expressionType.hpp"
#include <unordered_map>
#include <vector>

class Parser {
private:
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

public:
  Parser(Lexer lexer): lexer(lexer) {}

};
