#include "Visitors/typeCheckingVisitor.hpp"

#include "Expressions/ReturnExpression.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/ifExpression.hpp"
#include "Expressions/programExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"

#include "iostream"

void typeCheckingVisitor::visitTerminalExpression(
    TerminalExpression *terminal) {
  type = terminal->getType();
}

void typeCheckingVisitor::visitBinaryExpression(BinaryExpression *expression) {
  expression->getLHS()->accept(this);
  std::string lhsType = type;
  expression->getRHS()->accept(this);
  std::string rhsType = type;

  std::vector<std::string> boolOperators = {">","<", "==", "!="};

  if (lhsType == rhsType) {
    if (std::find(boolOperators.begin(), boolOperators.end(), expression->getOPType()) != boolOperators.end()){ // check if operator is a conditional operator
      type = "bool";
    }else{
      type = lhsType;
    }
    expression->setType(lhsType);
  } else {
    throw std::invalid_argument("Binary operation with mismatching types: " +
                                lhsType + " and " + rhsType + "\n");
  }
}

void typeCheckingVisitor::visitVariableAssignmentExpression(
    VariableAssignmentExpression *variable) {
  variable->getValueExpression()->accept(this);
  if (variable->getType() != type) {
    throw std::invalid_argument(
        "variable assignment operation with mismatching types: " +
        variable->getType() + " and " + type + "\n");
  } else {

    typeTable.top().insert(
        {variable->getVariable()->getName(), variable->getType()});
    variable->setType(type);
  }
}

void typeCheckingVisitor::visitVariableExpression(
    VariableExpression *variable) {

  std::stack<std::unordered_map<std::string, std::string>> tmpStack = typeTable;

  while (!tmpStack.empty()) {
    if (tmpStack.top().find(variable->getName()) != tmpStack.top().end()) {
      type = tmpStack.top()[variable->getName()];
      break;
    }
    tmpStack.pop();
  }
  variable->setType(type);
}

void typeCheckingVisitor::visitBlockExpression(BlockExpression *block) {
  typeTable.push({});
  std::vector<BaseExpression *> blockInstructions = block->getInstructions();
  std::string blockType = "";
  for (int i = 0; i < blockInstructions.size(); i++) {
    BaseExpression *expr = blockInstructions[i];
    expr->accept(this);
    if (dynamic_cast<ReturnExpression *>(expr) != nullptr) {
      if (type == blockType || blockType == "") {
        blockType = type;
      } else {
        throw std::invalid_argument(
            "Block must not have different return types");
      }
    }
  }
  if (blockType == "") {
    blockType = type;
  }
  block->setType(blockType);
  typeTable.pop();
}

void typeCheckingVisitor::visitReturnExpression(ReturnExpression *returnExpr) {
  returnExpr->getExpr()->accept(this);
  returnExpr->setType(type);
}

void typeCheckingVisitor::visitIfExpression(IfExpression *IfExpr) {
  IfExpr->getCondition()->accept(this);
  if (type != "bool") {
    throw std::invalid_argument("Conditionals must be of type 'bool'");
  }  
  std::string thenType, elseType;
  IfExpr->getThenBlock()->accept(this);
  thenType = type;
  if(IfExpr->getElseBlock() != nullptr){
    IfExpr->getElseBlock()->accept(this);
  }
  elseType = type;
  if (thenType == elseType) {
    IfExpr->setType(thenType);
    type = thenType;
  } else {
    throw std::invalid_argument("Conditional blocks must be of same type");
  }
}

void typeCheckingVisitor::visitFunctionDeclaration(
    FunctionDeclaration *FuncDeclExpr) {
  typeTable.push({});
  std::vector<std::string> argTypes;
  for (auto &arg : FuncDeclExpr->getArgs()) {
    argTypes.push_back(arg.first);
    typeTable.top()[arg.second] = arg.first;
  } 
  functionTypes[FuncDeclExpr->getName()] = FuncDeclExpr->getReturnType();
  FuncDeclExpr->getBody()->accept(this);
  if (FuncDeclExpr->getReturnType() != type){
    throw std::invalid_argument(
        "Function declared type does not match block type: " +
        FuncDeclExpr->getReturnType() + ", " + type);
  }
  FuncDeclExpr->setType(type);
  typeTable.pop();
  functionArgTypes[FuncDeclExpr->getName()] = argTypes;
}

void typeCheckingVisitor::visitFunctionCall(FunctionCall *FuncCallExpr) {
  std::vector<std::string> argTypes = functionArgTypes[FuncCallExpr->getName()];
  std::vector<std::string> argInputTypes;
  for (auto &arg : FuncCallExpr->getArgs()) {
    arg->accept(this);
    argInputTypes.push_back(type);
  }
  for (int i = 0; i < argTypes.size(); i++) {
    if (argTypes[i] != argInputTypes[i]) {
      throw std::invalid_argument(
          "Function called with incorrect argument types");
    }
  }
  type = functionTypes[FuncCallExpr->getName()];

  FuncCallExpr->setType(type);
}

void typeCheckingVisitor::visitProgramExpression(ProgramExpression *program) {
  for (auto funcDecl : program->getFunctions()) {
    funcDecl->accept(this);
  }
  program->setType(type);
}

void typeCheckingVisitor::visitVariableReassignmentExpression(
    VariableReassignmentExpression *variable) {

  variable->getVariable()->accept(this);
  variable->getValueExpression()->accept(this);
  if (variable->getVariable()->getType() == type) {
    variable->setType(type);
  } else {
    throw std::invalid_argument("Variable reassingment to different type");
  }
}
