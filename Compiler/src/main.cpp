#include "../src/Lexer/parser.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>

#include <stdio.h>

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
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/IR/LegacyPassManager.h"



extern BaseExpression *rootAST;
extern FILE* yyin;

int main(int argc, char **argv) {

  std::string inputFile;
  if (argc != 2){
    std::cout << "file error";
    return 1;
  }

  yyin = fopen(argv[1], "r");
  if (!yyin) {
    perror("Input file not found");
    return 1;
  }

  LLVM_Visitor visitor;

  yyparse();

  rootAST->accept(&visitor);

// print IR for debug
  visitor.getResult()->print(llvm::outs());
  llvm::outs() << "\n";


/* COMPILE TO .O FILE*/

  // get current architecture and initialize compiler
  auto TargetTriple = llvm::sys::getDefaultTargetTriple();

  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();

  std::string Error;
  auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

  // Print an error and exit if target not found
  if (!Target) {
    llvm::errs() << Error;
    return 1;
  }

  auto CPU = "generic";
  auto Features = "";

  llvm::TargetOptions opt;
  auto RM = std::optional<llvm::Reloc::Model>();
  auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

  visitor.TheModule->setDataLayout(TargetMachine->createDataLayout());
  visitor.TheModule->setTargetTriple(TargetTriple);


  std::string outputFilename = "output.o";
  std::error_code errorCode;
  llvm::raw_fd_ostream dest(outputFilename, errorCode, llvm::sys::fs::OF_None);

  if (errorCode) {
    llvm::errs() << "Could not open file: " << errorCode.message();
    return 1;
  }

  llvm::legacy::PassManager pass;
  auto FileType = llvm::CodeGenFileType::ObjectFile;

  if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
    llvm::errs() << "TargetMachine can't emit a file of this type";
    return 1;
  }

  pass.run(*visitor.TheModule);
  dest.flush();

  return 0;
}
