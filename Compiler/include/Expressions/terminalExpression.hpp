#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

#include "iostream"

class TerminalExpression : public BaseExpression {
private:
  int intValue;
  bool boolValue;
  float floatValue;
  char charValue;

public:
  TerminalExpression(int value) : intValue(value) {
    type = "int";
    std::cout << type << std::endl;
  }
  TerminalExpression(bool value) : boolValue(value) {
    type = "boolean";
    std::cout << type << std::endl;
  }
  TerminalExpression(float value) : floatValue(value) {
    type = "float";
    std::cout << type << std::endl;
  }
  TerminalExpression(char value) : charValue(value) {
    type = "char";
    std::cout << type << std::endl;
  }
  int getIntValue() { return intValue; }
  bool getBoolValue() { return boolValue; }
  float getFloatValue() { return floatValue; }
  char getCharValue() { return charValue; }
  void accept(BaseVisitor *visitor) override;
};
