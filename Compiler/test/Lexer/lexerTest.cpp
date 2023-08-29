#include "Lexer/lexer.hpp"
#include "Token/token.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Lexer correctly identifies single-digit integers", "[Lexer]") {
  Lexer lexer("3");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "3");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);
}

TEST_CASE("Lexer correctly identifies multi-digit integers", "[Lexer]") {
  Lexer lexer("42");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "42");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 3);
  REQUIRE(lexer.getPosition() == 2);
}

TEST_CASE("Lexer disallows leading zeros for multi-digit integers", "[Lexer]") {
  Lexer lexer("042");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() ==
          TokenType::UNKNOWN); // Adjust based on how you handle errors
  // Optionally check line and column if you find it relevant for this test case
}

TEST_CASE("Lexer correctly identifies '0' as an integer", "[Lexer]") {
  Lexer lexer("0");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "0");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);
}

TEST_CASE("Lexer correctly ignores whitespace", "[Lexer]") {
  Lexer lexer("  42");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "42");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 5);
  REQUIRE(lexer.getPosition() == 4);
}

TEST_CASE("Lexer correctly identifies unknown tokens", "[Lexer]") {
  Lexer lexer("a");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::UNKNOWN);
  REQUIRE(token.getValue() == "");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 1);
  REQUIRE(lexer.getPosition() == 0);
}

TEST_CASE("Lexer can identify '+' as Plus token", "[Lexer]") {
  Lexer lexer("+");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::PLUS);
  REQUIRE(token.getValue() == "+");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);
}

// write some more test cases for the '+' token
// when the string contains both integers and '+'
// use a new token for each call of getNextToken()

TEST_CASE("Lexer can lex '1+2' correctly", "[Lexer]") {
  Lexer lexer("1+2");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "1");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);

  Token secondToken = lexer.getNextToken();
  REQUIRE(secondToken.getType() == TokenType::PLUS);
  REQUIRE(secondToken.getValue() == "+");
  REQUIRE(secondToken.getLine() == 1);
  REQUIRE(secondToken.getColumn() == 3);
  REQUIRE(lexer.getPosition() == 2);

  Token thirdToken = lexer.getNextToken();
  REQUIRE(thirdToken.getType() == TokenType::INTEGER);
  REQUIRE(thirdToken.getValue() == "2");
  REQUIRE(thirdToken.getLine() == 1);
  REQUIRE(thirdToken.getColumn() == 4);
  REQUIRE(lexer.getPosition() == 3);
}

TEST_CASE("Lexer can lex '1 + 2' correctly", "[Lexer]") {
  Lexer lexer("1 + 2");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "1");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);

  Token secondToken = lexer.getNextToken();
  REQUIRE(secondToken.getType() == TokenType::PLUS);
  REQUIRE(secondToken.getValue() == "+");
  REQUIRE(secondToken.getLine() == 1);
  REQUIRE(secondToken.getColumn() == 4);
  REQUIRE(lexer.getPosition() == 3);

  Token thirdToken = lexer.getNextToken();
  REQUIRE(thirdToken.getType() == TokenType::INTEGER);
  REQUIRE(thirdToken.getValue() == "2");
  REQUIRE(thirdToken.getLine() == 1);
  REQUIRE(thirdToken.getColumn() == 6);
  REQUIRE(lexer.getPosition() == 5);
}

TEST_CASE("Lexer can lex '1 + 2 + 3' correctly", "[Lexer]") {
  Lexer lexer("1 + 2 + 3");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "1");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);

  Token secondToken = lexer.getNextToken();
  REQUIRE(secondToken.getType() == TokenType::PLUS);
  REQUIRE(secondToken.getValue() == "+");
  REQUIRE(secondToken.getLine() == 1);
  REQUIRE(secondToken.getColumn() == 4);
  REQUIRE(lexer.getPosition() == 3);

  Token thirdToken = lexer.getNextToken();
  REQUIRE(thirdToken.getType() == TokenType::INTEGER);
  REQUIRE(thirdToken.getValue() == "2");
  REQUIRE(thirdToken.getLine() == 1);
  REQUIRE(thirdToken.getColumn() == 6);
  REQUIRE(lexer.getPosition() == 5);

  Token fourthToken = lexer.getNextToken();
  REQUIRE(fourthToken.getType() == TokenType::PLUS);
  REQUIRE(fourthToken.getValue() == "+");
  REQUIRE(fourthToken.getLine() == 1);
  REQUIRE(fourthToken.getColumn() == 8);
  REQUIRE(lexer.getPosition() == 7);

  Token fifthToken = lexer.getNextToken();
  REQUIRE(fifthToken.getType() == TokenType::INTEGER);
  REQUIRE(fifthToken.getValue() == "3");
  REQUIRE(fifthToken.getLine() == 1);
  REQUIRE(fifthToken.getColumn() == 10);
  REQUIRE(lexer.getPosition() == 9);
}

// lexer can lex odd whitespacing in between tokens

TEST_CASE("Lexer can lex '1+ 12+ 21' correctly", "[Lexer]") {
  Lexer lexer("1+ 12+ 21");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::INTEGER);
  REQUIRE(token.getValue() == "1");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);

  Token secondToken = lexer.getNextToken();
  REQUIRE(secondToken.getType() == TokenType::PLUS);
  REQUIRE(secondToken.getValue() == "+");
  REQUIRE(secondToken.getLine() == 1);
  REQUIRE(secondToken.getColumn() == 3);
  REQUIRE(lexer.getPosition() == 2);

  Token thirdToken = lexer.getNextToken();
  REQUIRE(thirdToken.getType() == TokenType::INTEGER);
  REQUIRE(thirdToken.getValue() == "12");
  REQUIRE(thirdToken.getLine() == 1);
  REQUIRE(thirdToken.getColumn() == 6);
  REQUIRE(lexer.getPosition() == 5);

  Token fourthToken = lexer.getNextToken();
  REQUIRE(fourthToken.getType() == TokenType::PLUS);
  REQUIRE(fourthToken.getValue() == "+");
  REQUIRE(fourthToken.getLine() == 1);
  REQUIRE(fourthToken.getColumn() == 7);
  REQUIRE(lexer.getPosition() == 6);

  Token fifthToken = lexer.getNextToken();
  REQUIRE(fifthToken.getType() == TokenType::INTEGER);
  REQUIRE(fifthToken.getValue() == "21");
  REQUIRE(fifthToken.getLine() == 1);
  REQUIRE(fifthToken.getColumn() == 10);
  REQUIRE(lexer.getPosition() == 9);
}

// Test for multiple + signs in a row

TEST_CASE("Lexer treat '++' as two plus tokens", "[Lexer]") {
  Lexer lexer("++");
  Token token = lexer.getNextToken();
  REQUIRE(token.getType() == TokenType::PLUS);
  REQUIRE(token.getValue() == "+");
  REQUIRE(token.getLine() == 1);
  REQUIRE(token.getColumn() == 2);
  REQUIRE(lexer.getPosition() == 1);

  Token secondToken = lexer.getNextToken();
  REQUIRE(secondToken.getType() == TokenType::PLUS);
  REQUIRE(secondToken.getValue() == "+");
  REQUIRE(secondToken.getLine() == 1);
  REQUIRE(secondToken.getColumn() == 3);
  REQUIRE(lexer.getPosition() == 2);
}
