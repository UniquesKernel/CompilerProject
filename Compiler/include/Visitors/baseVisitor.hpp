#pragma once



class baseVisitor{
    public:
        void visitIntegerExpression(baseVisitor) = 0;
        void visitAdditionExpression(baseVisitor) = 0;
};