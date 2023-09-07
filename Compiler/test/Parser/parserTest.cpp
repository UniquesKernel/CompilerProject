#include <catch2/catch.hpp>
#include "Parser/parser.hpp"

TEST_CASE(
    "Parser test",
    "[Parser]") {
    const Lexer lexer("1+1");
    grammar_handler parser = grammar_handler();

    LRItem item = LRItem({BINARY_EXPRESSION, {EXPRESSION, PLUS, EXPRESSION}},2);
    LRItem item2 = LRItem({EXPRESSION, {INTEGER}},0);
    std::set<LRItem> item_list;
    item_list.insert(item);

    std::set<LRItem> closure = parser.closure(item_list);



    std::cout << "\n\n";

    for(LRItem item: closure){
        item.print();
    }

    REQUIRE(item_list.find(item2) == item_list.end());
}