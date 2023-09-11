#include <catch2/catch.hpp>

#include "Lexer/lexer.hpp"

TEST_CASE("Lexer Constructor", "[Lexer]") {
  SECTION("Can construct") {
    Lexer lexer("");

    REQUIRE(lexer.getTokens().size() == 0);
  }
}

TEST_CASE("Lexer Integer", "[Lexer]") {
  SECTION("Can tokenize integer") {
    GIVEN("Lexer with single digite Integer") {
      Lexer lexer("1");

      REQUIRE(lexer.getTokens().size() == 1);
      REQUIRE(lexer.getTokens()[0] == Token(Symbol::INTEGER, "1", 1, 1));
    }

    GIVEN("Lexer with multi digit Integer") {
      Lexer lexer("123");

      REQUIRE(lexer.getTokens().size() == 1);
      REQUIRE(lexer.getTokens()[0] == Token(Symbol::INTEGER, "123", 1, 1));
    }
  }

  SECTION("Can tokenize integer with whitespace") {
    GIVEN("Lexer with single digit Integer") {
      Lexer lexer(" 1");

      REQUIRE(lexer.getTokens().size() == 1);
      REQUIRE(lexer.getTokens()[0] == Token(Symbol::INTEGER, "1", 1, 2));
    }

    GIVEN("Lexer with multi digit Integer") {
      Lexer lexer(" 123");

      REQUIRE(lexer.getTokens().size() == 1);
      REQUIRE(lexer.getTokens()[0] == Token(Symbol::INTEGER, "123", 1, 2));
    }

    GIVEN("multiple Integers") {
      Lexer lexer(" 1 2 3 ");

      REQUIRE(lexer.getTokens().size() == 3);
      REQUIRE(lexer.getTokens()[0] == Token(Symbol::INTEGER, "1", 1, 2));
      REQUIRE(lexer.getTokens()[1] == Token(Symbol::INTEGER, "2", 1, 4));
      REQUIRE(lexer.getTokens()[2] == Token(Symbol::INTEGER, "3", 1, 6));
    }
  }
}

TEST_CASE("Binary Expressions", "[Lexer]") {
  SECTION("Addition Expression") {
    GIVEN("1 + 1") {
      Lexer lexer("1+1");

      REQUIRE(lexer.getTokens().size() == 3);
      REQUIRE(lexer.getTokens()[0] == Token(Symbol::INTEGER, "1", 1, 1));
      REQUIRE(lexer.getTokens()[1] == Token(Symbol::PLUS, "+", 1, 2));
      REQUIRE(lexer.getTokens()[2] == Token(Symbol::INTEGER, "1", 1, 3));
    }
  }
}
