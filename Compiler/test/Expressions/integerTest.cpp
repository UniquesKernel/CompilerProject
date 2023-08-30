#include "Expressions/integer.hpp"
#include "Token/token.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Integer expression created with integer token", "[Expression]") {
  Token token = Token(TokenType::INTEGER, "3", 1, 1);
  IntegerExpression integer = IntegerExpression(token);
  REQUIRE(integer.evaluate() == 3);
}

TEST_CASE("Integer expression throws error on wrong tokenType",
          "[Expression]") {
  Token token = Token(TokenType::PLUS, "+", 1, 1);
  REQUIRE_THROWS_WITH(IntegerExpression(token),
                      "Something is horribly wrong!!! An integerExpression was "
                      "created with the wrong tokenType: " +
                          std::to_string(TokenType::PLUS));
}