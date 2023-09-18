#include "../src/Lexer/parser.hpp"
#include <iostream>

typedef struct ResultNode {
  int value;
  struct ResultNode *next;
} ResultNode;

extern ResultNode *results;

int main(int argc, char **argv) {
  yyparse();

  ResultNode *current = results;
  while (current) {
    std::cout << "result: " << current->value << std::endl;
    current = current->next;
  }

  // Cleanup
  while (results) {
    ResultNode *temp = results;
    results = results->next;
    delete temp;
  }

  return 0;
}
