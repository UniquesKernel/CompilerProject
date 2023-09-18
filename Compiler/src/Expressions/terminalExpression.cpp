#include "Expressions/terminalExpression.hpp"

llvm::Value *TerminalExpression::accept(LLVM_Visitor *visitor) {
  return visitor->visitIntegerExpression(this);
}