#include "Visitors/baseVisitor.hpp"
#include "Expressions/baseExpression.hpp"
#include <string>
#include <unordered_map>


class typeCheckingVisitor: BaseVisitor{
private:
    std::string type;

public:
    std::unordered_map<std::string, std::string> typeTable;
    void visitTerminalExpression(TerminalExpression *terminal) override;
    void visitBinaryExpression(BinaryExpression *expression) override;
    void visitVariableAssignmentExpression(VariableAssignmentExpression *variable) override;
    void visitVariableExpression(VariableExpression *variable) override;
    void visitBlockExpression(BlockExpression *block) override;
    void visitReturnExpression(ReturnExpression *returnExpr) override;
    void visitIfExpression(IfExpression *IfExpr) override;
    void visitFunctionDeclaration(FunctionDeclaration *FuncDeclExpr) override;
    void visitFunctionCall(FunctionCall *FuncCallExpr) override;
};