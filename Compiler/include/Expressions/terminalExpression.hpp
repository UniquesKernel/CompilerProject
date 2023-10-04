#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

enum TerminalType {
  INT, 
  BOOLEAN, 
  FLOAT,
  CHAR,
};

class TerminalExpression : public BaseExpression {
private:
  TerminalType type;
  int intValue;
  bool boolValue;
  float floatValue;
  char charValue;

public:
  TerminalExpression(int value) : type(INT), intValue(value) {}
  TerminalExpression(bool value) : type(BOOLEAN), boolValue(value) {}
  TerminalExpression(float value) : type(FLOAT), floatValue(value) {}
  TerminalExpression(char value) : type(CHAR), charValue(value) {}
  int getIntValue() { return intValue; }
  bool getBoolValue() { return boolValue; }
  float getFloatValue() { return floatValue; }
  char getCharValue() { return charValue; }
  TerminalType getType() { return type; }
  void accept(LLVM_Visitor *visitor) override;
};
