#include <iostream>
#include "DataFeed.h"
#include "MovingAverageStrategy.h"
#include "Broker.h"
#include "Backtester.h"

int main() {
    
    DataFeed feed("data/sample_data.csv");

    //Short and long period for the moving average strategy
    MovingAverageStrategy strategy(2, 3);

    //Initialise broker with 10,000 cash and 10 trade size
    Broker broker(10000.00, 10);

    std::cout << "Running backtest...\n";

    Backtester backtester(feed, strategy, broker);

    backtester.run();

    std::cout << "Final equity: " << broker.getLastEquity() << "\n";
    std::cout << "Final cash position: " << broker.getCash()
              << " postion: " << broker.getPosition() << "\n";
              
    return 0;
}