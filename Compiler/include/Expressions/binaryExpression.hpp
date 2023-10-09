#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <memory>

class BinaryExpression : public BaseExpression {
private:
  std::unique_ptr<BaseExpression> lhs;
  std::unique_ptr<BaseExpression> rhs;
  char operatorType;

public:
  BinaryExpression(std::unique_ptr<BaseExpression> lhs, char operatorType, std::unique_ptr<BaseExpression> rhs)
      : lhs(std::move(lhs)), rhs(std::move(rhs)), operatorType(operatorType) {}
  BaseExpression* getLHS() const { return lhs.get(); }
  BaseExpression* getRHS() const { return rhs.get(); }
  char getType() const { return operatorType; }
  void accept(LLVM_Visitor *visitor) override;
  
  static BinaryExpression* createBinaryExpression(BaseExpression* lhs_raw, char op, BaseExpression* rhs_raw);

  };
