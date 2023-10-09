#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <memory>

class BinaryExpression : public BaseExpression {
private:
  BaseExpression *lhs;
  BaseExpression *rhs;
  char operatorType;

public:
  BinaryExpression(BaseExpression *lhs, char operatorType, BaseExpression *rhs)
      : lhs(lhs), operatorType(operatorType), rhs(rhs) { 
        if(lhs->getType() == rhs->getType()){
          type=lhs->getType();
        }else{
          throw std::invalid_argument("Binary opperator must have matching types: " + TerminalTypeStrings[lhs->getType()] + " " + operatorType + " " + TerminalTypeStrings[rhs->getType()]);
        }
      }
  BaseExpression *getLHS() { return lhs; }
  BaseExpression *getRHS() { return rhs; }
  char getType() { return type; }
  void accept(LLVM_Visitor *visitor) override;
  
  static BinaryExpression* createBinaryExpression(BaseExpression* lhs_raw, char op, BaseExpression* rhs_raw);

  };
