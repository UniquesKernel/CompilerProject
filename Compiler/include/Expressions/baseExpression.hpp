#pragma once

#include "Visitors/llvmVisitor.hpp"

class BaseExpression {
public:
  virtual llvm::Value *accept(LLVM_Visitor *visitor) = 0;
};