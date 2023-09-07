#include "Parser/parser.hpp"

// void grammar_handler::populateExpressionLists(){
//     for(Symbol symbol: Symbol){
//         if (grammar.find(symbol) == grammar.end()){
//             terminalExpression.insert(symbol);
//         }else{
//             nonTerminalExpression.insert(symbol);
//         }
//     }
// }

// void parser::populateMaps(){
//     for(Symbol symbol: nonTerminalExpression()){
//         std::vector rules = grammar[symbol];
//         for(ProductionRule rule: rules){
//             first[symbol]=(rule.right[0]);
//             for int i; i<rule.right.size(); i++){
//                 if(terminalExpression.find(rule.right[i])!=terminalExpression.end()){
//                     follower
//                 }
//             }
//         }
//     }
// }


std::set<LRItem> grammar_handler::closure(const LRItem& input_item){
    std::set<LRItem> closure_items;
    closure_items.insert(input_item);
    bool items_added = true;
int count = 0;
    while(items_added){
        items_added = false;
        std::set<LRItem> new_items;
        for(LRItem item: closure_items){
            if(item.dotPosition < item.productionRule.right.size()){
                Symbol symbol = item.productionRule.right[item.dotPosition];
                if (grammar.find(symbol) != grammar.end()){
                    for( const ProductionRule& productionRule : grammar[symbol]){
                        LRItem new_item = LRItem(productionRule, 0);
                        new_items.insert(new_item);
                    }
                }
            }
        }
        for(LRItem item: new_items){
            if(closure_items.find(item) == closure_items.end()){
                closure_items.insert(item);
                items_added=true;
            }
        }
    }
    return closure_items;
}




void grammar_handler::calculateStates(const LRItem& start){

    states.insert(closure(start));
    bool state_added = true;

    while(state_added){
        state_added = false;
        for(std::set<LRItem> state : states){
            for(LRItem item : state){
                if(item.dotPosition < item.productionRule.right.size()){
                    LRItem new_item = LRItem(item.productionRule, item.dotPosition+1);
                    std::set<LRItem> new_state = closure(new_item);
                    if(states.find(new_state) == states.end()){
                        states.insert(new_state);
                        state_added = true;
                    }
                }
            }
        }
    }
}

















// std::set<LRItem> Parser::closure(const std::set<LRItem>& items){
//     std::set<LRItem> closure_items = items;

//     bool items_added = true;

//     while(items_added){
//         items_added = false;
//         std::set<LRItem> items_to_add;

//         for(const LRItem& item : closure_items){
//             if (item.dotPosition < item.productionRule.right.size()){
//                 ExpressionType symbol = item.productionRule.right[item.dotPosition];

//                 if (grammar.find(symbol) != grammar.end()){

//                     for( const ProductionRule& productionRule : grammar[symbol]){
//                         LRItem new_item = LRItem(productionRule, 0);
//                         items_to_add.insert(new_item);
//                     }
//                 }
//             }
//         }
              
//         for(const LRItem& item : items_to_add){
//             if((closure_items.find(item) == closure_items.end())){
//                 closure_items.insert(item);
//                 items_added=true;
//             }
//         }
//     };
//     return closure_items;
// }

// std::set<LRItem> Parser::goTo_state(const std::set<LRItem>& items, const ExpressionType& symbol){
//     std::set<LRItem> new_items;

//     for(const LRItem item : items){
//         if(item.dotPosition < item.productionRule.right.size() &&
//         item.productionRule.right[item.dotPosition] == symbol){
//             LRItem new_item = LRItem(item.productionRule, item.dotPosition + 1);
//             new_items.insert(new_item);
//         }
//     }
//     return new_items;
// }

// void Parser::construct_action_table(){
//     std::set<LRItem> start;
//     // = {
//     //     {{EXPRESSION, {TERMINAL_EXPRESSION}}, 0},
//     // };
//     start.insert(LRItem({BINARY_EXPRESSION, {EXPRESSION, BINARY_OPERATOR_EXPRESSION, TERMINAL_EXPRESSION}}, 0));
//     // start.insert(LRItem({EXPRESSION, {TERMINAL_EXPRESSION}}, 0));
//     // start.insert(LRItem({EXPRESSION, {BINARY_EXPRESSION}}, 0));

//     std::stack<std::set<LRItem>> item_sets;
//     item_sets.push(closure(start));
//     item_set_mapping[item_sets.top()] = 0;

//     while (!item_sets.empty()){
//         std::set<LRItem> current_item_set = item_sets.top();
//         item_sets.pop();
        
//         for(const LRItem item: current_item_set){
//             if (item.dotPosition < item.productionRule.right.size()){
//                 ExpressionType symbol = item.productionRule.right[item.dotPosition];
//                 std::set<LRItem> new_item_set = closure(goTo_state(current_item_set, symbol));

//                 if(item_set_mapping.find(new_item_set) == item_set_mapping.end()){
//                     item_set_mapping[new_item_set] = item_set_mapping.size();
//                     item_sets.push(new_item_set);
//                 }
            
//                 int current_state = item_set_mapping[current_item_set];
//                 int next_state = item_set_mapping[new_item_set];

//                 if(grammar.find(symbol) == grammar.end()){
//                     action_table[current_state][symbol] = "s" + std::to_string(next_state);
//                 }
//             }
//             else if(item.dotPosition == item.productionRule.right.size()){
//                 int current_state = item_set_mapping[current_item_set];
//                 action_table[current_state][EOF_EXPRESSION] = "r";
//             }
//         }
//     }
// }

// void Parser::display_states(){
//         // Display all states and their closures
//     int state_count = 0;
//     for (const auto& mapping : item_set_mapping) {
//         const std::set<LRItem>& state_items = mapping.first;
//         std::cout << "State " << state_count++ << ":\n";
//         for (const LRItem& item : state_items) {
//             std::cout << item.productionRule.left << " -> ";
//             for (int i = 0; i < item.productionRule.right.size(); i++) {
//                 if (i == item.dotPosition) std::cout << ". ";
//                 std::cout << item.productionRule.right[i] << " ";
//             }
//         }
//         std::cout << "\n";  // For clarity between states
//     }
// }
