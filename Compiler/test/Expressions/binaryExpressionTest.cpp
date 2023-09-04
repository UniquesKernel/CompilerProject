#include <catch2/catch.hpp>

#include "Expression/binaryExpression.hpp"
#include "Token/token.hpp"
#include "Visitor/evaluatorVisitor.hpp"

TEST_CASE("A binary Expression can be created", "[binaryExpression]") {
  Token fistIntegerToken = Token(TokenType::INTEGER, "1", 1, 1);
  Token plusToken = Token(TokenType::PLUS, "+", 1, 1);
  Token secondIntegerToken = Token(TokenType::INTEGER, "2", 1, 1);

  ExpressionPtr left = std::make_unique<TerminalExpression>(fistIntegerToken);
  ExpressionPtr right =
      std::make_unique<TerminalExpression>(secondIntegerToken);

  BinaryExpression binaryExpression(plusToken, std::move(left),
                                    std::move(right));

  EvaluatorVisitor evaluatorVisitor;

  binaryExpression.accept(evaluatorVisitor);

  REQUIRE(evaluatorVisitor.getResult<int>() == 3);
}
