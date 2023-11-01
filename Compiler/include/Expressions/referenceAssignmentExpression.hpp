#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <memory>

class ReferenceAssignmentExpression : public BaseExpression {
  std::string identifier;
  std::string referenceIdentifier;
  llvm::Value* referenceValue = nullptr;
  bool isMutable;

  public:
  ReferenceAssignmentExpression(std::string identifier, std::string referenceIdentifier, std::string type, bool isMutable) : identifier(identifier), referenceIdentifier(referenceIdentifier), isMutable(isMutable) {
    this->type = type;
  }
  std::string getIdentifier() { return identifier; }
  std::string getReferenceIdentifier() { return referenceIdentifier; }
  llvm::Value* getReferenceValue() { return referenceValue; }
  void setReferenceValue(llvm::Value* value) { referenceValue = value; }
  bool isVarMutable() { return isMutable; }
  void accept(BaseVisitor *visitor) override { 
    visitor->visitReferenceAssignmentExpression(this);
  }

  std::string mapToType() {
    if (referenceValue->getType()->isIntegerTy(64)) {
      return "&int";
    } else if (referenceValue->getType()->isFloatTy()) {
      return "&float";
    } else if (referenceValue->getType()->isIntegerTy(8)) {
      return "&char";
    }
    return "";
  }
};
