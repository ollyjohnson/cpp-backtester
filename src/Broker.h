#pragma once

#include <string>
#include <vector>
#include "Bar.h"
#include "Strategy.h"

class Broker {
public:
    Broker(double initialCash, int tradeSize);

    void onSignal(Signal signal, const Bar& bar);
    void updateEquity(const Bar& bar);

    double getCash() const;
    int getPosition() const;
    double getLastEquity() const;
    const std::vector<double>& getEquityCurve() const;
    const std::vector<std::string>& getEquityDates() const;

private:
    double cash_;
    int position_;
    int tradeSize_;

    double lastEquity_{0.0};
    std::vector<double> equityCurve_;
    std::vector<std::string> equityDates_;
};