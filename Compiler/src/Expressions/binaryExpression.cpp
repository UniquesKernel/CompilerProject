#include "Expressions/binaryExpression.hpp"

void BinaryExpression::accept(BaseVisitor *visitor) {
  visitor->visitBinaryExpression(this);
}

BinaryExpression *
BinaryExpression::createBinaryExpression(BaseExpression *lhs_raw, char op,
                                         BaseExpression *rhs_raw) {
  std::cout << "create binary";
  std::unique_ptr<BaseExpression> lhs(lhs_raw);
  std::unique_ptr<BaseExpression> rhs(rhs_raw);

  if (!lhs || !rhs) {
    throw std::invalid_argument("Null pointer argument");
  }

  return new BinaryExpression(std::move(lhs), op, std::move(rhs));
}
