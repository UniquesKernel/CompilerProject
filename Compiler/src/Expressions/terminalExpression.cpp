#include "Expression/terminalExpression.hpp"
#include "Token/token.hpp"
#include <functional>
#include <iostream>
#include <map>

TerminalExpression::TerminalExpression(const Token &token) {
  const std::map<Symbol, std::function<void()>> converter = {
      {Symbol::INTEGER,
       [this, token]() { value = std::stoi(token.getValue()); }},
  };

  converter.at(token.getSymbol())();
}
