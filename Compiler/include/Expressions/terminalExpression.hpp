#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

class TerminalExpression : public BaseExpression {
private:
  int value;

public:
  TerminalExpression(int value) : value(value) {}
  int getValue() { return value; }
  void accept(LLVM_Visitor *visitor) override;
};