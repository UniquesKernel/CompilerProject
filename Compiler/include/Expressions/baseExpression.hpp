#pragma once

class LLVM_Visitor;

class BaseExpression {
public:
  virtual void accept(LLVM_Visitor *visitor) = 0;
};
