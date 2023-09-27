#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

enum TerminalType {
  INT, 
  BOOLEAN, 
};

class TerminalExpression : public BaseExpression {
private:
  TerminalType type;
  int intValue;
  bool boolValue;

public:
  TerminalExpression(int value) : type(INT), intValue(value) {}
  TerminalExpression(bool value) : type(BOOLEAN), boolValue(value) {}
  int getIntValue() { return intValue; }
  bool getBoolValue() { return boolValue; }
  TerminalType getType() { return type; }
  void accept(LLVM_Visitor *visitor) override;
};
