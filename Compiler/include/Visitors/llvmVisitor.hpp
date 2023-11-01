#pragma once

#include "Visitors/baseVisitor.hpp"

#include "Expressions/baseExpression.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/FixedPointBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include <llvm-18/llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <memory>

#include <stack>
#include <unordered_map>
#include <unordered_set>

class LLVM_Visitor : public BaseVisitor {
private:
  llvm::Value *llvm_result;
  void initializeBinaryOperatorFunctionTable();
  llvm::Type *getLLVMType(std::string type);

public:
  llvm::Value *getResult() { return llvm_result; }

  std::unique_ptr<llvm::LLVMContext> TheContext;
  std::unique_ptr<llvm::IRBuilder<>> Builder;
  std::unique_ptr<llvm::Module> TheModule;
  std::stack<std::unordered_map<std::string, llvm::AllocaInst *>>
      symbolTableStack;
  std::stack<std::unordered_set<std::string>> mutableVars;
  std::unordered_map<
      std::string,
      std::unordered_map<std::string, std::function<llvm::Value *(
                                          llvm::Value *, llvm::Value *)>>>
      dispatchTable;

  LLVM_Visitor() {
    // Open a new context and module.
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("my cool jit", *TheContext);

    // Create a new builder for the module.
    Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);

    llvm::Function *func_printf = TheModule->getFunction("printf");
    if (!func_printf) {
      llvm::PointerType *Pty = llvm::PointerType::get(
          llvm::IntegerType::get(TheModule->getContext(), 8), 0);
      llvm::FunctionType *FuncTy9 = llvm::FunctionType::get(
          llvm::IntegerType::get(TheModule->getContext(), 64), true);

      func_printf = llvm::Function::Create(
          FuncTy9, llvm::GlobalValue::ExternalLinkage, "printf", *TheModule);
      func_printf->setCallingConv(llvm::CallingConv::C);

      llvm::AttributeList func_printf_PAL;
      func_printf->setAttributes(func_printf_PAL);
    }
  }

  void visitTerminalExpression(TerminalExpression *terminal) override;
  void visitBinaryExpression(BinaryExpression *expression) override;
  void visitVariableAssignmentExpression(
      VariableAssignmentExpression *variable) override;
  void visitReferenceAssignmentExpression(
      ReferenceAssignmentExpression *variable) override;
  void visitVariableExpression(VariableExpression *variable) override;
  void visitBlockExpression(BlockExpression *block) override;
  void visitReturnExpression(ReturnExpression *returnExpr) override;
  void visitIfExpression(IfExpression *IfExpr) override;

  void visitFunctionDeclaration(FunctionDeclaration *FuncDeclExpr) override;
  void visitFunctionCall(FunctionCall *FuncCallExpr) override;
  void visitProgramExpression(ProgramExpression *program) override;

  void visitVariableReassignmentExpression(
      VariableReassignmentExpression *variable) override;
  // Helper functions
  llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,
                                           const std::string &VarName,
                                           llvm::Type *varType) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                           TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(varType, nullptr, VarName);
  }
  llvm::Type *getLLVMType(std::string type);

  void callPrintFunction(char *format, llvm::Value *input);
};
