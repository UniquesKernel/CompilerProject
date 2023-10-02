#include "Expressions/variableExpression.hpp"

void VariableAssignmentExpression::accept(LLVM_Visitor *visitor) {
  visitor->visitVariableAssignmentExpression(this);
}

void VariableExpression::accept(LLVM_Visitor *visitor) {
  visitor->visitVariableExpression(this);
}