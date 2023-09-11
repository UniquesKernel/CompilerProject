#include "Utility/token.hpp"
#include "Utility/symbol.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Constuctor", "[Token]") {
  SECTION("Can construct Token") {
    Token token(Symbol::INTEGER, "1", 1, 1);
    REQUIRE(token.getSymbol() == Symbol::INTEGER);
    REQUIRE(token.getValue() == "1");
    REQUIRE(token.getLine() == 1);
    REQUIRE(token.getColumn() == 1);
  }
}
