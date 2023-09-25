#pragma once
#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"

enum VarType{
    INTEGER,
    FLOAT,
    BOOL,
    CHAR,
};

class VariableAssignmentExpression : public BaseExpression {
    private:
        std::string name;
        BaseExpression * valueExpression;

    public:
        VariableAssignmentExpression(BaseExpression * valueExpression, std::string name) : valueExpression(valueExpression), name(name) {}
        BaseExpression* getValueExpression(){ return valueExpression; }
        std::string getName(){ return name; }
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