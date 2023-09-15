#pragma once

#include "Expressions/baseExpression.hpp"
#include "Visitors/llvmVisitor.hpp"


class BinaryExpression: public BaseExpression{
    private:
        BaseExpression* lhs;
        BaseExpression* rhs;
        char type;

    public:
        BinaryExpression(BaseExpression* lhs, BaseExpression* rhs):lhs(lhs),rhs(rhs){}
        BaseExpression* getLHS() {return lhs;}
        BaseExpression* getRHS() {return rhs;}
        llvm::Value* accept(LLVM_Visitor *visitor) override;
};