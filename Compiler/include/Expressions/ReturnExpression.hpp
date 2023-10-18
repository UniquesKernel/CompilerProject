#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

class ReturnExpression : public BaseExpression {
public:
  ReturnExpression(BaseExpression *expr) : expr(expr) {}
  BaseExpression *getExpr() { return expr; }

  void accept(BaseVisitor *visitor) { visitor->visitReturnExpression(this); }

private:
  BaseExpression *expr;
};
