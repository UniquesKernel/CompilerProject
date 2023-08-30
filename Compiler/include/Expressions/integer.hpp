#pragma once

#include "Expressions/expression.hpp"
#include "Token/token.hpp"

class IntegerExpression : public TerminalExpression<int> {

protected:
  int converter(std::string input) override { return std::stoi(input); }
  bool verifyTokenType(TokenType) override;

public:
  IntegerExpression(const Token &inputToken);
};