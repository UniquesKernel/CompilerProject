#pragma once

#include "Expressions/baseExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <string>
class FunctionDeclaration : public BaseExpression {
  private:
    std::string name;
    std::string type;
    BlockExpression* body;

  public:
    FunctionDeclaration(std::string type, std::string name, BlockExpression* body) : name(name), type(type), body(body) {
    std::cout << "FunctionDeclaration Constructor" << std::endl;
  }

    std::string getName() { return name; }
    std::string getType() { return type; }
    BlockExpression* getBody() { return body; }
    void accept(LLVM_Visitor *visitor) override { visitor->visitFunctionDeclaration(this); }
};
