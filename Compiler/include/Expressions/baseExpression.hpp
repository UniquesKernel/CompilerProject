#pragma once

#include "Visitors/llvmVisitor.hpp"

class BaseExpression {
public:
  virtual void accept(LLVM_Visitor *visitor) = 0;
};