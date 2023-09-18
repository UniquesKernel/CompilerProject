#include "Expressions/terminalExpression.hpp"

void TerminalExpression::accept(LLVM_Visitor *visitor) {
  visitor->visitIntegerExpression(this);
}