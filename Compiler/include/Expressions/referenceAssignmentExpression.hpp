#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <memory>

class ReferenceAssignmentExpression : public BaseExpression {
  std::string identifier;
  std::string referenceIdentifier;
  BaseExpression *referenceValue;
  bool isMutable;

public:
  ReferenceAssignmentExpression(std::string identifier,
                                std::string referenceIdentifier,
                                std::string type,
                                BaseExpression *referenceValue, bool isMutable)
      : identifier(identifier), referenceIdentifier(referenceIdentifier),
        referenceValue(referenceValue), isMutable(isMutable) {
    this->type = type;
  }
  std::string getIdentifier() { return identifier; }
  std::string getReferenceIdentifier() { return referenceIdentifier; }
  BaseExpression *getReferenceValue() { return referenceValue; }
  bool isVarMutable() { return isMutable; }
  void accept(BaseVisitor *visitor) override {
    visitor->visitReferenceAssignmentExpression(this);
  }
};
