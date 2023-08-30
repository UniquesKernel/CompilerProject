#include "Token/token.hpp"
#include <catch2/catch.hpp>

TEST_CASE(
    "Token class can be instantiated with correct integer type and getValue()",
    "[Token]") {
  const Token token(TokenType::INTEGER, "3", 1, 1);
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "3");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 1);
}

TEST_CASE("Token class can be instantiated with multi-digit integers",
          "[Token]") {
  const Token token(TokenType::INTEGER, "42", 1, 1);
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "42");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 1);
}

TEST_CASE("Token class can be instantiated to represent leading zeros",
          "[Token]") {
  const Token token(TokenType::UNKNOWN, "042", 1, 1);
  REQUIRE(token.getType() ==
          TokenType::UNKNOWN); // Adjust based on how you handle errors
  REQUIRE(token.getValue() == "042");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 1);
}

TEST_CASE("Token class can be instantiated with '0'", "[Token]") {
  const Token token(TokenType::INTEGER, "0", 1, 1);
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "0");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 1);
}
