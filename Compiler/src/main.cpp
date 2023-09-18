#include "../src/Lexer/parser.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"

typedef struct ResultNode {
  int value;
  struct ResultNode *next;
} ResultNode;

extern ResultNode *results;
int main(int argc, char **argv) {
  TerminalExpression int1 = TerminalExpression(1);
  TerminalExpression int2 = TerminalExpression(5);

  BinaryExpression adder = BinaryExpression(&int1, &int2);

  BinaryExpression adder2 = BinaryExpression(&int1, &adder);

  LLVM_Visitor visitor;

  llvm::Value *addition = adder2.accept(&visitor);

  addition->print(llvm::outs());
  llvm::outs() << '\n';

  // visitor.Builder->CreateRet(addition);

  // visitor.TheModule->print(llvm::outs(), nullptr);
  yyparse();

  ResultNode *current = results;
  while (current) {
    std::cout << "result: " << current->value << std::endl;
    current = current->next;
  }

  // Cleanup
  while (results) {
    ResultNode *temp = results;
    results = results->next;
    delete temp;
  }

  return 0;
}
