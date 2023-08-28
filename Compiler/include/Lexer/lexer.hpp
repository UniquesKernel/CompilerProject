#pragma once

#include <string>

class Lexer {
public:
  Lexer();
  ~Lexer();
  std::string lex(std::string input);
};
