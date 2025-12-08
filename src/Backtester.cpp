#include "Backtester.h"

Backtester::Backtester(DataFeed& feed, Strategy& strategy, Broker& broker)
    : feed_(feed),
      strategy_(strategy),
      broker_(broker) {}

void Backtester::run() {
    while (feed_.hasNext()) {
        const Bar& bar = feed_.next();
        Signal signal = strategy_.onBar(bar);
        broker_.onSignal(signal, bar);
        broker_.updateEquity(bar);
    }
}

double Backtester::finalEquity() const {
    return broker_.getLastEquity();
}