#pragma once

#include "Bar.h"

/**Enum clas to express signal types*/
enum class Signal {
    Hold,
    Buy,
    Sell
};

/**Abstract strategy class that has virtual constructor and onBar functions 
 * that enable polymorphism as you can decide at runtime which strategy to call*/
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual Signal onBar(const Bar& bar) = 0;
};