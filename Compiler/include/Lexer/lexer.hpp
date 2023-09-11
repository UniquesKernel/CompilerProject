#pragma once

#include "Utility/token.hpp"
#include <string>
#include <vector>

class Lexer {
private:
  std::string source;
  int position;
  int line;
  int column;
  std::vector<Token> tokens;

  void advance(int amount = 1);
  void tokenize();
  Token getNextToken();

public:
  Lexer(std::string source) : source(source), position(0), line(1), column(1) {
    tokenize();
  };
  std::vector<Token> getTokens() const { return tokens; };
};
