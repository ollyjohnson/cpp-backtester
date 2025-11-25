#include <iostream>
#include "DataFeed.h"

int main() {
    
    DataFeed feed("data/sample_data.csv");

    std::cout << "Iterating over bars from DataFeed:\n";

    while (feed.hasNext()) {
        const Bar& bar = feed.next();
        std::cout << bar.date << " close=" << bar.close << "\n";
    }

    return 0;
}