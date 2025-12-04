#include <iostream>
#include "DataFeed.h"
#include "MovingAverageStrategy.h"
#include "Broker.h"

int main() {
    
    DataFeed feed("data/sample_data.csv");

    //Short and long period for the moving average strategy
    MovingAverageStrategy strategy(2, 3);

    //Initialise broker with 10,000 cash and 10 trade size
    Broker broker(10000.00, 10);

    std::cout << "Running backtest...\n";

    while (feed.hasNext()) {
        const Bar& bar = feed.next();

        Signal signal = strategy.onBar(bar);
        broker.onSignal(signal, bar);
        broker.updateEquity(bar);

        std::cout << bar.date 
            << " close=" << bar.close
            << " signal=" << (signal == Signal::Buy ? "BUY" : signal == Signal::Sell ? "SELL" : "HOLD")
            << " cash=" << broker.getCash()
            << " position=" << broker.getPosition()
            << " equity=" << broker.getLastEquity() 
            << "\n";
    }

    std::cout << "Final equity: " << broker.getLastEquity() << "\n";
    return 0;
}