#include <catch2/catch.hpp>
#include "Lexer/lexer.hpp"

TEST_CASE("Lexer Test", "[lexer]") {
    GIVEN("A lexer") {
        Lexer lexer;
        WHEN("lex is called") {
            std::string input = "hello";
            std::string output = lexer.lex(input);
            THEN("the output is the same as the input") {
                REQUIRE(output == input);
            }
        }
    }
}
