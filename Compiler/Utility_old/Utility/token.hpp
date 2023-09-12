#pragma once

#include "Utility/symbol.hpp"
#include <string>

class Token {
private:
  const Symbol symbol;
  const std::string value;
  const int line;
  const int column;

public:
  Token(Symbol symbol, std::string value, int line, int column)
      : symbol(symbol), value(value), line(line), column(column){};

  bool operator==(const Token &other) const {
    return symbol == other.symbol && value == other.value &&
           line == other.line && column == other.column;
  }
  bool operator!=(const Token &other) const { return !(*this == other); }

  Symbol getSymbol() const { return symbol; };
  std::string getValue() const { return value; };
  int getLine() const { return line; };
  int getColumn() const { return column; };
};
