#pragma once
#include <string>

class BaseVisitor;

enum TerminalType {
  INT,
  BOOLEAN,
  FLOAT,
  CHAR,
};

// use this for error messages
const std::string TerminalTypeStrings[4] = {"int", "bool", "float", "char"};

class BaseExpression {
protected:
  std::string type;

public:
  virtual void accept(BaseVisitor *visitor) = 0;
  std::string getType() { return type; }
};
