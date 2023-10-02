#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"
#include <iostream>

enum VarType{
    INTEGER,
    FLOAT,
    BOOL,
    CHAR,
};

class VariableAssignmentExpression : public BaseExpression {
    private:
        VariableExpression *variable;
        BaseExpression * valueExpression;
        bool isMutable;

    public:
        VariableAssignmentExpression(BaseExpression * valueExpression, VariableExpression* variable, bool isMutable) : valueExpression(valueExpression),
                                                                variable(variable), isMutable(isMutable) {}
        BaseExpression* getValueExpression(){ return valueExpression; }
        VariableExpression* getVariable(){ return variable; }
        bool isVarMutable(){ return isMutable; }
        void accept(LLVM_Visitor *visitor) override;
    };

class VariableExpression : public BaseExpression {
    private:
        const std::string name;

    public:
        VariableExpression(std::string name) : name(name) {}
        std::string getName(){ return name; }
        void accept(LLVM_Visitor *visitor) override;
    };