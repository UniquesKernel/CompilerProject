#include "Expressions/binaryExpression.hpp"

void BinaryExpression::accept(LLVM_Visitor *visitor) {
  visitor->visitBinaryExpression(this);
}