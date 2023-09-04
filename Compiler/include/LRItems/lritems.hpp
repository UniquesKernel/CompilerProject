#pragma once

#include "ProductionRule/productionRule.hpp"

class LRItem {
private:  
  ProductionRule rule;
  int dotPosition;

public:
  LRItem(ProductionRule rule, int dotPosition): rule(rule), dotPosition(dotPosition) {}
};
