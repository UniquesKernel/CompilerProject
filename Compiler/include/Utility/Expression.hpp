#pragma once

#include <iostream>
#include <string>

class Expression {
public:
    virtual ~Expression() {}
    virtual void accept(class ExpressionVisitor& visitor) = 0; // for visitor pattern
};

class LiteralExpression : public Expression {
public:
    LiteralExpression(int v) : value(v) {}
    int getValue() const { return value; }
    void accept(class ExpressionVisitor& visitor) override;

private:
    int value;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(Expression* l, Expression* r) : left(l), right(r) {}
    Expression* getLeft() const { return left; }
    Expression* getRight() const { return right; }
    void accept(class ExpressionVisitor& visitor) override;

private:
    Expression* left;
    Expression* right;
};

class ExpressionVisitor {
public:
    virtual void visit(LiteralExpression& literal) = 0;
    virtual void visit(BinaryExpression& binary) = 0;
};

class PrintVisitor : public ExpressionVisitor {
public:
    void visit(LiteralExpression& literal) override {
        std::cout << literal.getValue();
    }

    void visit(BinaryExpression& binary) override {
        std::cout << "(";
        binary.getLeft()->accept(*this);
        std::cout << " + ";
        binary.getRight()->accept(*this);
        std::cout << ")";
    }
};

