#include "Lexer/lexer.hpp"
#include "Utility/symbol.hpp"
#include "Utility/token.hpp"
#include <iostream>
#include <regex>
#include <stdexcept>
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

  if (position == source.length()) {
    return Token(Symbol::END_OF_FILE, "", line, column);
  }

  if (position < source.length()) {
    std::vector<std::pair<std::regex, Symbol>> tokenPatterns = {
        {std::regex("^0\\b|^([1-9][0-9]*)"), Symbol::INTEGER},
        {std::regex("^\\+"), Symbol::PLUS},
    };

    std::smatch match;
    std::string tmp = source.substr(position);
    for (const auto &tokenPattern : tokenPatterns) {
      if (std::regex_search(tmp, match, tokenPattern.first)) {
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

void Lexer::tokenize() {
  while (position < source.length()) {
    Token token = getNextToken();

    if (token.getSymbol() != Symbol::END_OF_FILE) {
      tokens.push_back(token);
    }
  }
}
