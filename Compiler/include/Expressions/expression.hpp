#pragma once

#include "Token/token.hpp"
#include <string>

template <typename T> class Expression {

public:
  virtual T evaluate() = 0;
};

template <typename T> class TerminalExpression : Expression<T> {
protected:
  T value;
  virtual T converter(std::string) = 0;
  virtual bool verifyTokenType(TokenType inputType) = 0;

public:
  T evaluate() { return value; }
  // TerminalExpression(const Token& inputToken){
  //     if(!verifyTokenType(inputToken)){throw std::runtime_error("Something is
  //     horribly wrong!!! A TerminalExpression was created with the wrong
  //     tokenType: " + std::to_string(inputToken.getType))} value =
  //     converter(inputToken.getValue());
  // }
};