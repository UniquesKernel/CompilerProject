#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>

class VariableAssignmentExpression : public BaseExpression {
private:
  VariableExpression *variable;
  BaseExpression *valueExpression;
  bool isMutable;

public:
  VariableAssignmentExpression(BaseExpression *valueExpression,
                               VariableExpression *variable, bool isMutable,
                               std::string inType)
      : valueExpression(valueExpression), variable(variable),
        isMutable(isMutable) {
    type = inType;
  }
  BaseExpression *getValueExpression() { return valueExpression; }
  VariableExpression *getVariable() { return variable; }
  bool isVarMutable() { return isMutable; }
  void accept(BaseVisitor *visitor) override;
};

class VariableExpression : public BaseExpression {
private:
  const std::string name;
  bool isReference = false;

public:
  VariableExpression(std::string name) : name(name) {}
  VariableExpression(std::string name, bool isReference)
      : name(name), isReference(isReference) {}
  std::string getName() { return name; }
  bool getIsReference() { return isReference; }
  void accept(BaseVisitor *visitor) override;
};

class VariableReassignmentExpression : public BaseExpression {
private:
  VariableExpression *variable;
  BaseExpression *valueExpression;

public:
  VariableReassignmentExpression(BaseExpression *valueExpression,
                                 VariableExpression *variable)
      : variable(variable), valueExpression(valueExpression) {}
  BaseExpression *getValueExpression() { return valueExpression; }
  VariableExpression *getVariable() { return variable; }
  void accept(BaseVisitor *visitor) override;
};
