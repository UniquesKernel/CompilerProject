#pragma once

#include "Utility/symbol.hpp"
#include <string>
#include <iostream>

class Token {
private:
  Symbol symbol;
  std::string value;
  int line;
  int column;

public:
  Token(Symbol symbol, std::string value, int line, int column)
      : symbol(symbol), value(value), line(line), column(column){};
  Token() = default;

  Symbol getSymbol() const { return symbol; };
  std::string getValue() const { return value; };
  int getLine() const { return line; };
  int getColumn() const { return column; };

   void print() const {
        std::cout << "Type: " << static_cast<int>(symbol) 
                  << ", Lexeme: '" << value 
                  << "', Line: " << line
                  << ", Length: " << column << std::endl;
    }
};
