#include "MovingAverageStrategy.h"

#include <numeric>
#include <stdexcept>

MovingAverageStrategy::MovingAverageStrategy(int shortPeriod, int longPeriod) : shortPeriod_(shortPeriod), longPeriod_(longPeriod)
{
    if (shortPeriod_ <= 0 || longPeriod_ <= 0 || shortPeriod_ >= longPeriod_) {
        throw std::runtime_error("Invalid moving average periods");
    }
}

Signal MovingAverageStrategy::onBar(const Bar& bar) {
    //Store the new close in the MAStrat class
    closes_.push_back(bar.close);

    //If we dont have enough data for long MA, do nothing
    if (static_cast<int>(closes_.size()) < longPeriod_) {
        return Signal::Hold;
    }

    //Compute short and long moving averages
    double shortMA = computeMovingAverage(shortPeriod_);
    double longMA = computeMovingAverage(longPeriod_);

    if(!inPosition_ && shortMA > longMA){
        inPosition_ = true;
        return Signal::Buy;
    }
    if (inPosition_ && shortMA < longMA){
        inPosition_ = false;
        return Signal::Sell;
    }
    return Signal::Hold;
    
}

double MovingAverageStrategy::computeMovingAverage(int period) const {
    auto start = closes_.end() - period;
    auto end = closes_.end();

    double sum = std::accumulate(start, end, 0.0);
    return sum / static_cast<double>(period);
}