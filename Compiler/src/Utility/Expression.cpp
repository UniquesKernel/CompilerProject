#include "Utility/Expression.hpp"

void LiteralExpression::accept(ExpressionVisitor& visitor) {
    visitor.visit(*this);
}

void BinaryExpression::accept(ExpressionVisitor& visitor) {
    visitor.visit(*this);
}
