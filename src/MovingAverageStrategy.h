#pragma once

#include <vector>
#include "Strategy.h"

/**Class for a Simple Moving Average crossover strategy that 
 * inherits from the abstract virtual strategy class*/
class MovingAverageStrategy : public Strategy {
public:
    MovingAverageStrategy(int shortPeriod, int longPeriod);

    //Overrides the Strategy onBar virtual function
    Signal onBar(const Bar& bar) override;

private:
    int shortPeriod_;
    int longPeriod_;
    std::vector<double> closes_;
    bool inPosition_{false};

    double computeMovingAverage(int period) const;
};