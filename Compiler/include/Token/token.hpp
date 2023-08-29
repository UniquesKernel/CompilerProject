#pragma once

#include <string>

enum TokenType {
  INTEGER,
  PLUS,
  UNKNOWN,
};

class Token {
private:
  const TokenType type;
  const std::string value;
  const int line;
  const int column;

public:
  Token(TokenType type, std::string value, int line, int column)
      : type(type), value(value), line(line), column(column) {}

  TokenType getType() const { return type; }
  std::string getValue() const { return value; }
  int getLine() const { return line; }
  int getColumn() const { return column; }
};
