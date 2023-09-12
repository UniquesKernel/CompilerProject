#include "Utility/grammar.hpp"
#include "Utility/symbol.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

std::map<Symbol, std::string> symbolToString = {
    {Symbol::EXPRESSION, "EXPRESSION"},
    {Symbol::INTEGER, "INTEGER"},
    {Symbol::PLUS, "PLUS"},
    {Symbol::MINUS, "MINUS"},
    {Symbol::UNKNOWN, "UNKNOWN"},
    {Symbol::EPSILON, "EPSILON"},
    {Symbol::END_OF_FILE, "END_OF_FILE"},
    {Symbol::START, "START"},
    {Symbol::BINARY_EXPRESSION, "BINARY_EXPRESSION"},
    {Symbol::UNARY_EXPRESSION, "UNARY_EXPRESSION"}};

namespace Catch {
template <> struct StringMaker<std::map<Symbol, std::set<Symbol>>> {
  static std::string convert(const std::map<Symbol, std::set<Symbol>> &value) {
    std::string result = "{ ";

    for (const auto &mapItem : value) {
      result += symbolToString[mapItem.first];
      result += ": { ";

      for (const auto &setItem : mapItem.second) {
        result += symbolToString[setItem];
        result += ", ";
      }

      if (!mapItem.second.empty()) {
        result.pop_back();
        result.pop_back();
      }

      result += " }, ";
    }

    if (!value.empty()) {
      result.pop_back();
      result.pop_back();
    }

    result += " }";
    return result;
  }
};
} // namespace Catch

TEST_CASE("Grammar Constructor", "[grammar]") {
  std::vector<Rule> rules = {
      Rule(Symbol::EXPRESSION, {Symbol::INTEGER})
  };
  REQUIRE_NOTHROW(Grammar(rules));
}

TEST_CASE("Grammar can find terminal and non-terminal symbols", "[grammar]") {

  SECTION("Grammar can find all none-terminal symbols from Grammar rules") {
    GIVEN("A Grammar with one rule") {
      std::vector<Rule> rules = {
          Rule(Symbol::EXPRESSION, {Symbol::INTEGER})
      };
      Grammar grammar(rules);

      std::set<Symbol> expectedNonTerminals = {Symbol::EXPRESSION, Symbol::START};

      REQUIRE(grammar.getNonTerminals() == expectedNonTerminals);
    }

    GIVEN("A Grammar with two rules") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::PLUS, Symbol::INTEGER})
      };
      Grammar grammar(rules);

      std::set<Symbol> expectedNonTerminals = {Symbol::EXPRESSION, Symbol::START};
    }
  }

  SECTION("Grammar can find all terminal symbols from Grammar rules") {
    GIVEN("A Grammar with one rule") {
      std::vector<Rule> rules = {    
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
      };

      Grammar grammar(rules);

      std::set<Symbol> expectedTerminals = {Symbol::INTEGER};

      REQUIRE(grammar.getTerminals() == expectedTerminals);
    }

    GIVEN("A Grammar with two rules") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::PLUS, Symbol::INTEGER})
      };

      Grammar grammar(rules);

      std::set<Symbol> expectedTerminals = {Symbol::INTEGER, Symbol::PLUS};

      REQUIRE(grammar.getTerminals() == expectedTerminals);
    }

    GIVEN("A Grammar with three rules") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::PLUS, Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::MINUS, Symbol::INTEGER})
      };

      Grammar grammar(rules);

      std::set<Symbol> expectedTerminals = {Symbol::INTEGER, Symbol::PLUS, Symbol::MINUS};

      REQUIRE(grammar.getTerminals() == expectedTerminals);
    }
  }
}

TEST_CASE("Grammar can find the FirstSet of all symbols in the Grammar rules",
          "[Grammar]") {
  SECTION("Grammar can find the FirstSet of all symbols in a Grammar with one "
          "rule") {
    GIVEN("A Grammar with one rule") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFirstSets = {
          {Symbol::START, {Symbol::INTEGER}},
          {Symbol::EXPRESSION, {Symbol::INTEGER}},
          {Symbol::INTEGER, {Symbol::INTEGER}}};

      REQUIRE(grammar.getFirstSets() == expectedFirstSets);
    }

    GIVEN("A Grammar with two rules") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::PLUS, Symbol::INTEGER})
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFirstSets = {
          {Symbol::START, {Symbol::INTEGER}},
          {Symbol::EXPRESSION, {Symbol::INTEGER}},
          {Symbol::INTEGER, {Symbol::INTEGER}},
          {Symbol::PLUS, {Symbol::PLUS}}};

      REQUIRE(grammar.getFirstSets() == expectedFirstSets);
    }

    GIVEN("A Grammar where a non-terminal maps to EPSILON") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::EPSILON}),
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFirstSets = {
          {Symbol::START, {Symbol::EPSILON}},
          {Symbol::EXPRESSION, {Symbol::EPSILON}},
          {Symbol::EPSILON, {Symbol::EPSILON}}};

      REQUIRE(grammar.getFirstSets() == expectedFirstSets);
    }

    GIVEN("A Grammar with multiple rules for the same non-terminal") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::EPSILON})
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFirstSets = {
          {Symbol::START, {Symbol::INTEGER, Symbol::EPSILON}},
          {Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::EPSILON}},
          {Symbol::INTEGER, {Symbol::INTEGER}},
          {Symbol::EPSILON, {Symbol::EPSILON}}};

      REQUIRE(grammar.getFirstSets() == expectedFirstSets);
    }

    GIVEN("A Grammar with a chain of non-terminals") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::BINARY_EXPRESSION}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::BINARY_EXPRESSION, {Symbol::EXPRESSION, Symbol::PLUS, Symbol::EXPRESSION}),
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFirstSets = {
          {Symbol::START, {Symbol::INTEGER}},
          {Symbol::EXPRESSION, {Symbol::INTEGER}},
          {Symbol::BINARY_EXPRESSION, {Symbol::INTEGER}},
          {Symbol::INTEGER, {Symbol::INTEGER}},
          {Symbol::PLUS, {Symbol::PLUS}}};

      REQUIRE(grammar.getFirstSets() == expectedFirstSets);
    }

    GIVEN("A combination of all conditions") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::BINARY_EXPRESSION}),
        Rule(Symbol::BINARY_EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::BINARY_EXPRESSION, {Symbol::EXPRESSION, Symbol::PLUS, Symbol::EXPRESSION}),
        Rule(Symbol::UNARY_EXPRESSION, {Symbol::MINUS, Symbol::EXPRESSION}),
        Rule(Symbol::UNARY_EXPRESSION, {Symbol::EPSILON})
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFirstSets = {
          {Symbol::START, {Symbol::INTEGER}},
          {Symbol::EXPRESSION, {Symbol::INTEGER}},
          {Symbol::BINARY_EXPRESSION, {Symbol::INTEGER}},
          {Symbol::UNARY_EXPRESSION, {Symbol::MINUS, Symbol::EPSILON}},
          {Symbol::INTEGER, {Symbol::INTEGER}},
          {Symbol::PLUS, {Symbol::PLUS}},
          {Symbol::MINUS, {Symbol::MINUS}},
          {Symbol::EPSILON, {Symbol::EPSILON}},
      };

      REQUIRE(grammar.getFirstSets() == expectedFirstSets);
    }
  }
}

TEST_CASE("Grammar can find the FollowSet of all symbols in the Grammar rules",
          "[Grammar]") {
  SECTION("Grammar can find the follow set of all symbol in a grammar with one "
          "rule") {
    GIVEN("A Grammar with one rule") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFollowSets = {
          {Symbol::START, {Symbol::END_OF_FILE}},
          {Symbol::EXPRESSION, {Symbol::END_OF_FILE}}
      };

      REQUIRE(grammar.getFollowSets() == expectedFollowSets);
    }
  }
  SECTION("Grammar can find the follow set of all symbol in a grammar with two "
          "rules") {
    GIVEN("A Grammar with two rules") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::PLUS, Symbol::INTEGER}),
      };
      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFollowSets = {
        {Symbol::START, {Symbol::END_OF_FILE}},
        {Symbol::EXPRESSION, {Symbol::END_OF_FILE}}
      };

      REQUIRE(grammar.getFollowSets() == expectedFollowSets);
    }
  }

  SECTION("Grammar can find the follow set of all symbol in a grammar with "
          "three rules") {
    GIVEN("A Grammar with three rules") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::PLUS, Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER, Symbol::MINUS, Symbol::INTEGER}),
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFollowSets = {
          {Symbol::START, {Symbol::END_OF_FILE}},
          {Symbol::EXPRESSION, {Symbol::END_OF_FILE}}
      };

      REQUIRE(grammar.getFollowSets() == expectedFollowSets);
    }
  }

  SECTION("Grammar can find the follow set of all non-terminal symbols, with "
          "indirect recusive rules") {
    GIVEN("A Grammar with five recursive rules") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::BINARY_EXPRESSION}),
        Rule(Symbol::EXPRESSION, {Symbol::UNARY_EXPRESSION}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::BINARY_EXPRESSION, {Symbol::EXPRESSION, Symbol::PLUS, Symbol::EXPRESSION}),
        Rule(Symbol::UNARY_EXPRESSION, {Symbol::MINUS, Symbol::EXPRESSION}),
      };
      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFollowSets = {
          {Symbol::START, {END_OF_FILE}},
          {Symbol::EXPRESSION, {Symbol::PLUS, Symbol::MINUS, END_OF_FILE}},
          {Symbol::BINARY_EXPRESSION, {Symbol::PLUS}},
          {Symbol::UNARY_EXPRESSION, {Symbol::PLUS}},
      };

      REQUIRE(grammar.getFollowSets() == expectedFollowSets);
    }

    GIVEN("a Grammar with rules that include EPSILON") {
      std::vector<Rule> rules = {
        Rule(Symbol::EXPRESSION, {Symbol::BINARY_EXPRESSION}),
        Rule(Symbol::EXPRESSION, {Symbol::UNARY_EXPRESSION}),
        Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
        Rule(Symbol::EXPRESSION, {Symbol::EPSILON}),
        Rule(Symbol::BINARY_EXPRESSION, {Symbol::EXPRESSION, Symbol::PLUS, Symbol::EXPRESSION}),
        Rule(Symbol::UNARY_EXPRESSION, {Symbol::MINUS, Symbol::EXPRESSION}),
      };

      Grammar grammar(rules);

      std::map<Symbol, std::set<Symbol>> expectedFollowSets = {
          {Symbol::START, {END_OF_FILE}},
          {Symbol::EXPRESSION, {Symbol::PLUS, Symbol::END_OF_FILE}},
          {Symbol::BINARY_EXPRESSION, {Symbol::END_OF_FILE}},
          {Symbol::UNARY_EXPRESSION, {Symbol::END_OF_FILE}},
      };

      REQUIRE(grammar.getFollowSets() == expectedFollowSets);
    }
  }
}

/*
TEST_CASE("Parser test", "[Parser]") {
  std::unordered_map<Symbol, std::vector<Rule>> rules = {
      {Symbol::EXPRESSION,
       {
           Rule(Symbol::EXPRESSION, {Symbol::BINARY_EXPRESSION}),
           Rule(Symbol::EXPRESSION, {Symbol::UNARY_EXPRESSION}),
           Rule(Symbol::EXPRESSION, {Symbol::INTEGER}),
           Rule(Symbol::EXPRESSION, {Symbol::EPSILON}),
       }},
      {Symbol::BINARY_EXPRESSION,
       {
           Rule(Symbol::BINARY_EXPRESSION,
                {Symbol::EXPRESSION, Symbol::PLUS, Symbol::EXPRESSION}),
       }},
      {Symbol::UNARY_EXPRESSION,
       {
           Rule(Symbol::UNARY_EXPRESSION, {Symbol::MINUS, Symbol::EXPRESSION}),
       }}};

  Grammar grammar(rules);

  LRItem item = LRItem({BINARY_EXPRESSION, {EXPRESSION, PLUS, EXPRESSION}}, 0);
  LRItem item2 = LRItem({EXPRESSION, {INTEGER}}, 0);
  std::set<LRItem> item_list;
  item_list.insert(item);

  std::set<LRItem> closure = grammar.closure(item);

  grammar.calculateStates(item);

  std::cout << "\n\n";
  int count = 0;
  for (std::set<LRItem> state : grammar.states) {
    std::cout << "state " << count++ << "\n";
    for (LRItem item : state) {
      item.print();
    }
  }
  REQUIRE(item_list.find(item2) == item_list.end());
}
*/
