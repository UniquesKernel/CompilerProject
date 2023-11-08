#pragma once

#include "Visitors/baseVisitor.hpp"
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

struct VariableInfo {
  std::string name;
  unsigned int flags; // All flags collected in one variable

  // Define bit positions for each flag
  static const unsigned int isParamBit = 0;     // Bit 0
  static const unsigned int isMutableBit = 1;   // Bit 1
  static const unsigned int isReferenceBit = 2; // Bit 2
  static const unsigned int isBorrowedBit = 3;  // Bit 3

  // Constructor to initialize the struct with no flags set
  VariableInfo(const std::string &varName) : name(varName), flags(0) {}

  std::string getName() const { return name; }
  unsigned int getFlags() const { return flags; }

  // Methods to set flags
  void setParam() { flags |= (1 << isParamBit); }
  void setMutable() { flags |= (1 << isMutableBit); }
  void setReference() { flags |= (1 << isReferenceBit); }
  void setBorrowed() { flags |= (1 << isBorrowedBit); }

  // Methods to unset flags
  void unsetParam() { flags &= ~(1 << isParamBit); }
  void unsetMutable() { flags &= ~(1 << isMutableBit); }
  void unsetReference() { flags &= ~(1 << isReferenceBit); }
  void unsetBorrowed() { flags &= ~(1 << isBorrowedBit); }

  // Methods to check the flags
  bool isParam() const { return (flags & (1 << isParamBit)) != 0; }
  bool isMutable() const { return (flags & (1 << isMutableBit)) != 0; }
  bool isReference() const { return (flags & (1 << isReferenceBit)) != 0; }
  bool isBorrowed() const { return (flags & (1 << isBorrowedBit)) != 0; }
};

class BorrowChecker : public BaseVisitor {
public:
  BorrowChecker(){};
  void visitBinaryExpression(BinaryExpression *expression) override;
  void visitVariableAssignmentExpression(
      VariableAssignmentExpression *variable) override;
  void visitVariableExpression(VariableExpression *variable) override;
  void visitReferenceAssignmentExpression(
      ReferenceAssignmentExpression *variable) override;
  void visitTerminalExpression(TerminalExpression *terminal) override;
  void visitBlockExpression(BlockExpression *block) override;
  void visitIfExpression(IfExpression *ifExpr) override;
  void visitFunctionDeclaration(FunctionDeclaration *funcDeclExpr) override;
  void visitFunctionCall(FunctionCall *funcCallExpr) override;
  void visitReturnExpression(ReturnExpression *returnExpr) override;
  void visitProgramExpression(ProgramExpression *funcCallExpr) override;
  void visitVariableReassignmentExpression(
      VariableReassignmentExpression *variable) override;

private:
  // create symboltable
  std::stack<std::vector<VariableInfo>> symbolTable;
  std::unordered_map<std::string, std::vector<std::pair<std::string, bool>>>
      referenceMap;
};
