#pragma once

#include "ProductionRule/productionRule.hpp"
#include "symbols.hpp"
#include <iostream>


class LRItem {
private:  

public: 

    bool operator< (const LRItem& rhs) const{
        if(productionRule.left != rhs.productionRule.left){
            return productionRule.left < rhs.productionRule.left;
        }else if(dotPosition != rhs.dotPosition) {
            return dotPosition < rhs.dotPosition;
        }else if(productionRule.right.size() != rhs.productionRule.right.size()){
            return productionRule.right.size() < rhs.productionRule.right.size();
        }else{
            for(int i=0; i<productionRule.right.size(); i++){
                if(productionRule.right[i] < rhs.productionRule.right[i]){
                    return true;
                }
            }
            return false;
        }
    }

    bool operator== (const LRItem& rhs) const{
        return dotPosition == rhs.dotPosition &&
            productionRule.left == rhs.productionRule.left &&
            productionRule.right == rhs.productionRule.right;
    }


    void print(){
        std::cout << productionRule.left << " -> ";
            for (int i = 0; i < productionRule.right.size(); i++) {
                if (i == dotPosition) std::cout << ". ";
                std::cout << productionRule.right[i] << " ";
            }
            std::cout << "\n";
    }

    ProductionRule productionRule;
    int dotPosition;

    LRItem(ProductionRule rule, int dotPosition): productionRule(rule), dotPosition(dotPosition) {}
};

namespace std {
    template<>
    struct hash<LRItem> {
        std::size_t operator()(const LRItem& item) const {
            std::size_t h1 = std::hash<Symbol>{}(item.productionRule.left);
            std::size_t h2 = std::hash<int>{}(item.dotPosition);
            return h1 * (h2 + 1);
        }
    };

    // create a hash for std::set<LRItem>
    template<>
    struct hash<std::set<LRItem>> {
        std::size_t operator()(const std::set<LRItem>& items) const {
            std::size_t h = 0;
            for (const LRItem& item : items) {
                h ^= std::hash<LRItem>{}(item);
            }
            return h;
        }
    };
}