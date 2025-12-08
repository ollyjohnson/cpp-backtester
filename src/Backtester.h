# pragma once

# include "DataFeed.h"
# include "Strategy.h"
# include "Broker.h"

class Backtester {
public:
    Backtester(DataFeed& feed, Strategy& Strategy, Broker& broker);

    void run ();
    double finalEquity() const;

private:
    DataFeed& feed_;
    Strategy& strategy_;
    Broker& broker_;
};