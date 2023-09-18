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

  LLVM_Visitor visitor;

  TerminalExpression int1 = TerminalExpression(1);
  TerminalExpression int2 = TerminalExpression(2);
  TerminalExpression int4 = TerminalExpression(4);
  BinaryExpression add3 = BinaryExpression(&int1, '+', &int2);
  BinaryExpression sub1 = BinaryExpression(&add3, '-', &int2);
  BinaryExpression mul3 = BinaryExpression(&add3, '*', &sub1);
  BinaryExpression div2 = BinaryExpression(&int4, '/', &int2);
  BinaryExpression mod1 = BinaryExpression(&add3, '%', &int2);

  add3.accept(&visitor);
  visitor.getResult()->print(llvm::outs());
  llvm::outs() << '\n';

  sub1.accept(&visitor);
  visitor.getResult()->print(llvm::outs());
  llvm::outs() << '\n';

  mul3.accept(&visitor);
  visitor.getResult()->print(llvm::outs());
  llvm::outs() << '\n';

  div2.accept(&visitor);
  visitor.getResult()->print(llvm::outs());
  llvm::outs() << '\n';

  mod1.accept(&visitor);
  visitor.getResult()->print(llvm::outs());
  llvm::outs() << '\n';

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
