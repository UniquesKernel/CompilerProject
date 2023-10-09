#include "Expressions/variableExpression.hpp"

void VariableAssignmentExpression::accept(BaseVisitor *visitor) {
  visitor->visitVariableAssignmentExpression(this);
}

void VariableExpression::accept(BaseVisitor *visitor) {
  visitor->visitVariableExpression(this);
}