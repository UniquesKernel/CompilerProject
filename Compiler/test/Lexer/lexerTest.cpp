#include "Lexer/lexer.hpp"
#include <catch2/catch.hpp>
#include <string>

TEST_CASE("Lexer Test 2", "[lexer]") {
  Lexer lexer;
  std::string input = "int main() { return 0; }";
  REQUIRE(lexer.lex(input) == "int main() { return 0; }");
}
