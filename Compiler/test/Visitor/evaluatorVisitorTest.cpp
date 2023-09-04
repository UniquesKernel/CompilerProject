#include <catch2/catch.hpp>

#include "Expression/binaryExpression.hpp"
#include "Token/token.hpp"
#include "Visitor/evaluatorVisitor.hpp"
#include <limits>

TEST_CASE("Addition Properties with EvaluatorVisitor") {
  GIVEN("An EvaluatorVisitor and two integers") {
    EvaluatorVisitor evaluator;

    WHEN("Adding two positive integers") {
      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "5", 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "7", 1, 1));

      BinaryExpression binaryExpression(Token(TokenType::PLUS, "+", 1, 1),
                                        std::move(expr1), std::move(expr2));

      binaryExpression.accept(evaluator);

      THEN("The result should be the sum of the integers") {
        int result = evaluator.getResult<int>();
        REQUIRE(result == 5 + 7);
      }
    }

    WHEN("Adding a positive integer and zero") {
      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "5", 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "0", 1, 1));

      BinaryExpression binaryExpression(Token(TokenType::PLUS, "+", 1, 1),
                                        std::move(expr1), std::move(expr2));

      binaryExpression.accept(evaluator);

      THEN("The result should be the positive integer") {
        int result = evaluator.getResult<int>();
        REQUIRE(result == 5);
      }
    }

    WHEN("Adding a positive integer and its negation") {
      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "5", 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "-5", 1, 1));

      BinaryExpression binaryExpression(Token(TokenType::PLUS, "+", 1, 1),
                                        std::move(expr1), std::move(expr2));

      binaryExpression.accept(evaluator);

      THEN("The result should be zero") {
        int result = evaluator.getResult<int>();
        REQUIRE(result == 0);
      }
    }

    WHEN("Adding a positive integer and a negative integer") {
      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "5", 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "-7", 1, 1));

      BinaryExpression binaryExpression(Token(TokenType::PLUS, "+", 1, 1),
                                        std::move(expr1), std::move(expr2));

      binaryExpression.accept(evaluator);

      THEN("The result should be the difference of the absolute values") {
        int result = evaluator.getResult<int>();
        REQUIRE(result == 5 - 7);
      }
    }

    WHEN("Adding a negative integer and a positive integer") {
      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "-5", 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "7", 1, 1));

      BinaryExpression binaryExpression(Token(TokenType::PLUS, "+", 1, 1),
                                        std::move(expr1), std::move(expr2));

      binaryExpression.accept(evaluator);

      THEN("The result should be the difference of the absolute values") {
        int result = evaluator.getResult<int>();
        REQUIRE(result == -5 + 7);
      }
    }

    WHEN("adding two positive integers, the order of operation should not "
         "matter") {
      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "5", 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "7", 1, 1));
      std::unique_ptr<const Expression> expr3 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "5", 1, 1));
      std::unique_ptr<const Expression> expr4 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "7", 1, 1));

      BinaryExpression binaryExpression1(Token(TokenType::PLUS, "+", 1, 1),
                                         std::move(expr1), std::move(expr2));
      BinaryExpression binaryExpression2(Token(TokenType::PLUS, "+", 1, 1),
                                         std::move(expr4), std::move(expr3));

      binaryExpression1.accept(evaluator);
      int result1 = evaluator.getResult<int>();
      binaryExpression2.accept(evaluator);
      int result2 = evaluator.getResult<int>();

      THEN("The result should be the same") { REQUIRE(result1 == result2); }
    }

    WHEN("Adding two larger numbers") {
      int max = std::numeric_limits<int>::max();

      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, std::to_string(max), 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "1", 1, 1));

      BinaryExpression binaryExpression(Token(TokenType::PLUS, "+", 1, 1),
                                        std::move(expr1), std::move(expr2));

      THEN("The should throw an overflow error") {
        REQUIRE_THROWS_AS(binaryExpression.accept(evaluator),
                          std::overflow_error);
      }
    }

    WHEN("adding to large negative numbers") {
      int min = std::numeric_limits<int>::min();

      std::unique_ptr<const Expression> expr1 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, std::to_string(min), 1, 1));
      std::unique_ptr<const Expression> expr2 =
          std::make_unique<TerminalExpression>(
              Token(TokenType::INTEGER, "-1", 1, 1));

      BinaryExpression binaryExpression(Token(TokenType::PLUS, "+", 1, 1),
                                        std::move(expr1), std::move(expr2));

      THEN("The should throw an overflow error") {
        REQUIRE_THROWS_AS(binaryExpression.accept(evaluator),
                          std::underflow_error);
      }
    }
  }
}
