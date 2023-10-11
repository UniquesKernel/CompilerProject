#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <string>
class FunctionCall : public BaseExpression {
private:
  std::string name;
  std::vector<BaseExpression *> args;

public:
  FunctionCall(std::string name) : name(name) {
    std::cout << "FunctionCall Constructor" << std::endl;
  }
  FunctionCall(std::string name, std::vector<BaseExpression *> args)
      : name(name), args(args) {}
  std::string getName() { return name; }
  std::vector<BaseExpression *> getArgs() { return args; }
  void accept(LLVM_Visitor *visitor) override {
    visitor->visitFunctionCall(this);
  }
};
