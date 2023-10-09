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
  TerminalExpression(int value) : intValue(value) { type = INT; }
  TerminalExpression(bool value) : boolValue(value) { type = BOOLEAN; }
  TerminalExpression(float value) : floatValue(value) { type = FLOAT; }
  TerminalExpression(char value) : charValue(value) { type = CHAR; }
  int getIntValue() { return intValue; }
  bool getBoolValue() { return boolValue; }
  float getFloatValue() { return floatValue; }
  char getCharValue() { return charValue; }
  void accept(LLVM_Visitor *visitor) override;
};
