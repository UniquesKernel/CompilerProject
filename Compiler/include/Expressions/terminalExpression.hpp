#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

#include "iostream"

class TerminalExpression : public BaseExpression {
private:
  int intValue;
  bool boolValue;
  double floatValue;
  char charValue;

public:
  TerminalExpression(int value) : intValue(value) { type = "int"; }
  TerminalExpression(bool value) : boolValue(value) { type = "bool"; }
  TerminalExpression(double value) : floatValue(value) { type = "float"; }
  TerminalExpression(char value) : charValue(value) { type = "char"; }
  int getIntValue() { return intValue; }
  bool getBoolValue() { return boolValue; }
  double getFloatValue() { return floatValue; }
  char getCharValue() { return charValue; }
  void accept(BaseVisitor *visitor) override;
};
