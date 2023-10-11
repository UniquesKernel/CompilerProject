#pragma once

#include "Expressions/baseExpression.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <vector>
class ProgramExpression : BaseExpression {
private:
  std::vector<FunctionDeclaration *> functions;
  bool hasMainFunction = false;

public:
  ProgramExpression(std::vector<FunctionDeclaration *> functions)
      : functions(functions) {
    std::cout << "program creation" << std::endl;
  }
  bool getHasMainFunction() const { return hasMainFunction; }
  void setHasMainFunction(bool hasMain) { hasMainFunction = hasMain; }
  std::vector<FunctionDeclaration *> getFunctions() { return functions; }
  void accept(BaseVisitor *visitor) { visitor->visitProgramExpression(this); }
};
