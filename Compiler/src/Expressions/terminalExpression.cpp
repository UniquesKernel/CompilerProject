#include "Expressions/terminalExpression.hpp"

void TerminalExpression::accept(BaseVisitor *visitor) {
  visitor->visitTerminalExpression(this);
}
