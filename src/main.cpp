#include <iostream>
#include <algorithm>
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

    const auto& equity = broker.getEquityCurve();

    double total_return = ((equity.back() - equity.front())/equity.front()) * 100;

    std::cout << "Total return: " << total_return << " %\n";

    double peak = equity.front();
    double max_drawdown = 0.0;

    for(double e : equity){
        peak = std::max(e, peak);
        double dd = (peak-e) / peak * 100;
        max_drawdown = std::max(dd,max_drawdown);
    }

    std::cout << "Max Drawdown: " << max_drawdown << " %\n";

    broker.writeEquityCurve("results/equity_curve.csv");

    std::cout << "Final equity: " << broker.getLastEquity() << "\n";
    std::cout << "Final cash position: " << broker.getCash()
              << " postion: " << broker.getPosition() << "\n";
              
    return 0;
}