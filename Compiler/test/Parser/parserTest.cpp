#include <catch2/catch.hpp>
#include "Parser/parser.hpp"

TEST_CASE(
    "Parser test",
    "[Parser]") {
    const Lexer lexer("1+1");
    grammar_handler parser = grammar_handler();

    LRItem item = LRItem({BINARY_EXPRESSION, {EXPRESSION, PLUS, EXPRESSION}},0);
    LRItem item2 = LRItem({EXPRESSION, {INTEGER}},0);
    std::set<LRItem> item_list;
    item_list.insert(item);

    std::set<LRItem> closure = parser.closure(item);

    parser.calculateStates(item);

    std::cout << "\n\n";
    int count = 0;
    for(std::set<LRItem> state : parser.states){
        std::cout << "state " << count++ << "\n";
        for(LRItem item: state){
            item.print();
        }
    }
    REQUIRE(item_list.find(item2) == item_list.end());
}