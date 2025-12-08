#include "Broker.h"
#include <fstream>
#include <stdexcept>

Broker::Broker(double initialCash, int tradeSize)
 : cash_(initialCash), 
   position_(0), 
   tradeSize_(tradeSize) {}

void Broker::onSignal(Signal signal, const Bar& bar){
    if (signal == Signal::Buy){
        double cost = bar.close * static_cast<double>(tradeSize_);
        if (cash_ >= cost) {
            cash_ -= cost;
            position_ += tradeSize_;
        }
    } else if (signal == Signal::Sell){
        if (position_ > 0){
            double proceeds = bar.close * static_cast<double>(position_);
            cash_ += proceeds;
            position_ = 0;
        }
    }
}

void Broker::updateEquity(const Bar& bar){
    double equity = cash_ + static_cast<double>(position_) * bar.close;
    lastEquity_ = equity;
    equityDates_.push_back(bar.date);
    equityCurve_.push_back(equity);
}

double Broker::getCash() const {
    return cash_;
}

int Broker::getPosition() const {
    return position_;
}

double Broker::getLastEquity() const {
    return lastEquity_;
}

const std::vector<double>& Broker::getEquityCurve() const {
    return equityCurve_;
}

const std::vector<std::string>& Broker::getEquityDates() const {
    return equityDates_;
}

void Broker::writeEquityCurve(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    file << "date,equity" << "\n";
    for(int i=0; i<equityDates_.size(); i++){
        file << equityDates_[i] << "," << equityCurve_[i] << "\n"; 
    }

}