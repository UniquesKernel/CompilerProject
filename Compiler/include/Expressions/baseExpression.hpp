#pragma once
#include <string>

class LLVM_Visitor;

enum TerminalType {
  INT, 
  BOOLEAN, 
  FLOAT,
  CHAR,
};

// use this for error messages
const std::string TerminalTypeStrings[4] = {"INT", "BOOLEAN", "FLOAT", "CHAR"}; 


class BaseExpression {
  protected:
    TerminalType type;
  public:
    virtual void accept(LLVM_Visitor *visitor) = 0;
    TerminalType getType() { return type; }
};
