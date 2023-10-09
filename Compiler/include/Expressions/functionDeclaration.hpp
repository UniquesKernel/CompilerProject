#pragma once

#include "Expressions/baseExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <memory>
#include <string>
class FunctionDeclaration : public BaseExpression {
  private:
    std::string name;
    std::string returnType;
    std::vector<llvm::Type*> params;
    std::unique_ptr<BlockExpression> body;


  public:
    FunctionDeclaration(std::string name, std::string returnType, BlockExpression* body) : 
    name(name),
    returnType(returnType), 
    body(body) {}

    std::string getName() { return name; }
    std::string getReturnType() { return returnType; }
    std::vector<llvm::Type*> getParams() { return params; }
    BlockExpression* getBody() { return body.get(); }
    void accept(LLVM_Visitor *visitor) override { visitor->visitFunctionDeclaration(this); }
};

