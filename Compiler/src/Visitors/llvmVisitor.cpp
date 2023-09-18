#include "Visitors/llvmVisitor.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"

llvm::Value *
LLVM_Visitor::visitAdditionExpression(BinaryExpression *expression) {

  return Builder->CreateAdd(expression->getLHS()->accept(this),
                            expression->getRHS()->accept(this), "addtmp");
}

llvm::Value *LLVM_Visitor::visitIntegerExpression(TerminalExpression *integer) {
  return llvm::ConstantInt::get(*TheContext,
                                llvm::APInt(64, integer->getValue()));
}