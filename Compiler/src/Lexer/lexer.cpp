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
    advance();
  }

  if (position <= source.length()) {
    std::vector<std::pair<std::regex, Symbol>> tokenPatterns = {
        {std::regex("^0\\b|^([1-9][0-9]*)"), Symbol::INTEGER},
        {std::regex("^\\+"), Symbol::PLUS},
    };

    std::smatch match;
    for (const auto &tokenPattern : tokenPatterns) {
      if (std::regex_search(source.begin() + position, source.end(), match,
                            tokenPattern.first)) {
        value = match.str();
        Token token = Token(tokenPattern.second, value, line, column);
        advance(value.length());
        return token;
      }
    }
  }

  throw std::runtime_error("Invalid token at line " + std::to_string(line) +
                           ", column " + std::to_string(column));
}
