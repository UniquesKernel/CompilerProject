#include "Expression/terminalExpression.hpp"
#include "Token/token.hpp"
#include "Visitor/evaluatorVisitor.hpp"
#include <catch2/catch.hpp>

TEST_CASE("A terminal Expression can be created", "[terminalExpression]") {
  Token token(TokenType::INTEGER, "1", 1, 1);
  TerminalExpression terminalExpression(token);
  REQUIRE(std::get<int>(terminalExpression.getValue()) == 1);
}

TEST_CASE("A terminal Expression can be visited", "[terminalExpression]") {
  Token token(TokenType::INTEGER, "1", 1, 1);
  TerminalExpression terminalExpression = TerminalExpression(token);

  EvaluatorVisitor evaluatorVisitor;

  terminalExpression.accept(evaluatorVisitor);

  REQUIRE(evaluatorVisitor.getResult<int>() == 1);
}
