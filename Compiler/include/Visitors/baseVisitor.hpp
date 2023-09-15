#pragma once

class BinaryExpression;
class TerminalExpression;

template <typename T> class BaseVisitor{
    public:
        virtual T visitAdditionExpression(BinaryExpression* expression) = 0;
        virtual T visitIntegerExpression(TerminalExpression*) = 0;
};