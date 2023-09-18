#include "../src/Lexer/parser.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>
#include <llvm-18/llvm/Support/raw_ostream.h>

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

extern BaseExpression *rootAST;
int main(int argc, char **argv) {

  LLVM_Visitor visitor;

  yyparse();

  rootAST->accept(&visitor);

  visitor.getResult()->print(llvm::outs());
  llvm::outs() << "\n";

  return 0;
}
