#pragma once

#include "Expressions/baseExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <utility>
class FunctionDeclaration : public BaseExpression {
private:
  std::string name;
  std::string returnType;
  std::vector<std::pair<std::string, std::string>> args =
      std::vector<std::pair<std::string, std::string>>();
  std::unique_ptr<BlockExpression> body;

public:
  FunctionDeclaration(std::string name, std::string returnType,
                      BlockExpression *body,
                      std::vector<std::pair<std::string, std::string>> args)
      : name(name), body(body), returnType(returnType), args(args) {}
  FunctionDeclaration(std::string name, std::string returnType,
                      BlockExpression *body)
      : name(name), body(body), returnType(returnType) {}

  std::string getName() { return name; }
  std::vector<std::pair<std::string, std::string>> getArgs() { return args; }
  std::string getReturnType() { return returnType; }
  BlockExpression *getBody() { return body.get(); }
  void accept(LLVM_Visitor *visitor) override {
    visitor->visitFunctionDeclaration(this);
  }
};
