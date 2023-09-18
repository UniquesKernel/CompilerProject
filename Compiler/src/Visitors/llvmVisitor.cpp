#include "Visitors/llvmVisitor.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include <iostream>

void
LLVM_Visitor::visitBinaryExpression(BinaryExpression *expression) {
    expression->getLHS()->accept(this);
    llvm::Value* L = llvm_result;
    expression->getRHS()->accept(this);
    llvm::Value* R = llvm_result;
    char type = expression->getType();
    
    std::cout << type << std::endl;

    switch(type){
        case '+':
            llvm_result =  Builder->CreateAdd(L, R, "addtmp");
            break;
        case '-':
            llvm_result =  Builder->CreateSub(L, R, "subtmp");
            break;
        case '*':
            llvm_result =  Builder->CreateMul(L, R, "multmp");
            break;
        case '/':
            llvm_result =  Builder->CreateSDiv(L, R, "divtmp");
            break;
        case '%':
            llvm_result = Builder->CreateSRem(L, R, "modtmp");
            break;
        default:
            throw std::invalid_argument("PANIC");
    }
    
}

void LLVM_Visitor::visitIntegerExpression(TerminalExpression *integer) {
  llvm_result = llvm::ConstantInt::get(*TheContext,
                                        llvm::APInt(64, integer->getValue()));
}

