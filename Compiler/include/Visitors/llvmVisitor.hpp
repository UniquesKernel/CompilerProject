#pragma once

#include "Visitors/baseVisitor.hpp"

#include "Expressions/baseExpression.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/FixedPointBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include <llvm/IR/Verifier.h>
#include <memory>

#include <unordered_map>
#include <unordered_set>

class LLVM_Visitor : public BaseVisitor {
private:
  llvm::Value *llvm_result;

public:
  llvm::Value *getResult() { return llvm_result; }

  std::unique_ptr<llvm::LLVMContext> TheContext;
  std::unique_ptr<llvm::IRBuilder<>> Builder;
  std::unique_ptr<llvm::Module> TheModule;
  std::unordered_map<std::string, llvm::AllocaInst *> symbolTable;
  std::unordered_set<std::string> mutableVars;

  LLVM_Visitor() {
    // Open a new context and module.
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("my cool jit", *TheContext);

    // Create a new builder for the module.
    Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
  }

  void visitTerminalExpression(TerminalExpression *terminal) override;
  void visitBinaryExpression(BinaryExpression *expression) override;
  void visitVariableAssignmentExpression(VariableAssignmentExpression *variable) override;
  void visitVariableExpression(VariableExpression *variable) override;
  void visitBlockExpression(BlockExpression* block) override;
  void visitReturnExpression(ReturnExpression* returnExpr) override;
  void visitIfExpression(IfExpression* IfExpr) override;


  void visitFunctionDeclaration(FunctionDeclaration* FuncDeclExpr) override;
  void visitFunctionCall(FunctionCall* FuncCallExpr) override;

//Helper functions
  llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, const std::string &VarName) 
  {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(llvm::Type::getDoubleTy(*TheContext), nullptr, VarName);
  }

  llvm::Type* getLLVMType(std::string type);
};
