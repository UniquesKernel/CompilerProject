#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <string>
class FunctionCall : public BaseExpression {
  private: 
    std::string name;

  public:
    FunctionCall(std::string name) : name(name) {
      std::cout << "FunctionCall Constructor" << std::endl;
    }
    std::string getName() { return name; }
    void accept(LLVM_Visitor *visitor) override { visitor->visitFunctionCall(this); }
};
