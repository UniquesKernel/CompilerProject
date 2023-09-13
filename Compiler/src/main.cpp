#include "../src/Lexer/parser.hpp"
#include <iostream>

extern int result;


int main(int argc, char **argv)
{
    yyparse();
  return 0;

}
