#include "Lexer/lexer.hpp"
#include "Token/token.hpp"

#include <regex>
#include <string>
#include <vector>

void Lexer::advance(int amount) {
  position += amount;
  column += amount;
}

Token Lexer::getNextToken() {
  std::string value = "";
  while (position <= source.length() && isspace(source[position])) {
    position++;
    column++;
  }

  if (position <= source.length()) {
    std::vector<std::pair<std::regex, TokenType>> tokenPatterns = {
        {std::regex("\\b0\\b|^([1-9][0-9]*)"), TokenType::INTEGER},
        {std::regex("^\\+"), TokenType::PLUS},
    };

    std::smatch match;
    for (const auto &tokenPattern : tokenPatterns) {
      if (std::regex_search(source.begin() + position, source.end(), match,
                            tokenPattern.first)) {
        value = match.str();
        advance(value.length());
        return Token(tokenPattern.second, value, line, column);
      }
    }
  }

  return Token(TokenType::UNKNOWN, "", line, column);
}
