#pragma once

#include "Token/token.hpp"
#include <string>

class Lexer {
private:
  const std::string source;
  int position;
  int line;
  int column;

  void advance(int amount = 1);

public:
  Lexer(std::string source) : source(source), position(0), line(1), column(1) {}
  int getPosition() const { return position; }
  Token getNextToken();
};
