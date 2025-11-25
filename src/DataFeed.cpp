#include "DataFeed.h"

#include <stdexcept>
#include <iostream>

DataFeed::DataFeed(const std::string& filePath) {
    loadFakeData();
}

bool DataFeed::hasNext() const {
    return currentIndex_ < bars_.size();
}

const Bar& DataFeed::next() {
    if (!hasNext()) {
        throw std::runtime_error("No more bars in DataFeed");
    }
    return bars_[currentIndex_++];
}

void DataFeed::loadFakeData() {
    bars_.push_back(Bar{"2020-01-02", 100.0, 101.5, 99.8, 101.2, 123456});
    bars_.push_back(Bar{"2020-01-03", 101.2, 102.0, 100.5, 101.8, 98765});
    bars_.push_back(Bar{"2020-01-06", 101.8, 103.0, 101.0, 102.5, 150000});
}


void DataFeed::loadFromCsv(const std::string&){
    
}