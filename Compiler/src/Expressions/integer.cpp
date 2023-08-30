#include "Expressions/integer.hpp"
#include <stdexcept>

bool IntegerExpression::verifyTokenType(TokenType inputType) {
  return inputType == TokenType::INTEGER;
}

IntegerExpression::IntegerExpression(const Token &inputToken) {
  if (!verifyTokenType(inputToken.getType())) {

    throw std::runtime_error(
        "Something is horribly wrong!!! An integerExpression was created with "
        "the wrong tokenType: " +
        std::to_string(inputToken.getType()));
  }
  value = converter(inputToken.getValue());
}
