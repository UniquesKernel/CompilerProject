#include "Expression/terminalExpression.hpp"
#include "Token/token.hpp"
#include <functional>
#include <iostream>
#include <map>

TerminalExpression::TerminalExpression(const Token &token) {
  const std::map<TokenType, std::function<void()>> converter = {
      {TokenType::INTEGER,
       [this, token]() { value = std::stoi(token.getValue()); }},
  };

  converter.at(token.getType())();
}
