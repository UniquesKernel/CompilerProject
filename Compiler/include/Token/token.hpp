#pragma once

#include <string>
#include "symbols.hpp"


class Token {
private:
  const Symbol symbol;
  const std::string value;
  const int line;
  const int column;

public:
  Token(Symbol symbol, std::string value, int line, int column)
      : symbol(symbol), value(value), line(line), column(column) {}

  Symbol getSymbol() const { return symbol; }
  std::string getValue() const { return value; }
  int getLine() const { return line; }
  int getColumn() const { return column; }
};
