#pragma once

#include "Visitors/baseVisitor.hpp"

class baseExpression{
    void visit(baseVisitor) = 0;
}