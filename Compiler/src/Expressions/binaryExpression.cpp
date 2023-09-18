#include "Expressions/binaryExpression.hpp"

llvm::Value *BinaryExpression::accept(LLVM_Visitor *visitor) {
  return visitor->visitAdditionExpression(this);
}