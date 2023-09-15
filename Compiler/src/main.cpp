#include <iostream>
#include "Visitors/llvmVisitor.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"

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

int main() {
  TerminalExpression int1 = TerminalExpression(1);
  TerminalExpression int2 = TerminalExpression(5);

  BinaryExpression adder = BinaryExpression(&int1, &int2);
  
  BinaryExpression adder2 = BinaryExpression(&int1, &adder);

  LLVM_Visitor visitor;

  llvm::Value* addition = adder2.accept(&visitor);

  addition->print(llvm::outs());
  llvm::outs() << '\n';
 
  // visitor.Builder->CreateRet(addition);

  // visitor.TheModule->print(llvm::outs(), nullptr);
}
