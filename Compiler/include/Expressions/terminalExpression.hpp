#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

class TerminalExpression : public BaseExpression {
private:
  int intValue;
  bool boolValue;
  float floatValue;
  char charValue;

public:
  TerminalExpression(int value) : intValue(value) { type = "int"; }
  TerminalExpression(bool value) : boolValue(value) { type = "boolean"; }
  TerminalExpression(float value) : floatValue(value) { type = "float"; }
  TerminalExpression(char value) : charValue(value) { type = "char"; }
  int getIntValue() { return intValue; }
  bool getBoolValue() { return boolValue; }
  float getFloatValue() { return floatValue; }
  char getCharValue() { return charValue; }
  void accept(BaseVisitor *visitor) override;
};
