#include "DataFeed.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

DataFeed::DataFeed(const std::string& filePath) {
    try {
        loadFromCsv(filePath);
    } catch (const std::exception& ex) {
        std::cerr << "Failed to load CSV from '" << filePath << "': " << ex.what() << "\n";
        std::cerr << "Falling back to fake in-memory data.\n";
        loadFakeData();
    }
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


void DataFeed::loadFromCsv(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;

    if (!std::getline(file, line)) {
        throw std::runtime_error("File is empty");
    }

    bars_.clear();
    currentIndex_ = 0;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string dateStr;
        std::string openStr, highStr, lowStr, closeStr, volumeStr;

        std::getline(ss, dateStr, ',');
        std::getline(ss, openStr, ',');
        std::getline(ss, highStr, ',');
        std::getline(ss, lowStr, ',');
        std::getline(ss, closeStr, ',');
        std::getline(ss, volumeStr, ',');

        if (dateStr.empty()) {
            continue;
        }

        Bar bar;
        bar.date = dateStr;
        bar.open = std::stod(openStr);
        bar.high = std::stod(highStr);
        bar.low = std::stod(lowStr);
        bar.close = std::stod(closeStr);
        bar.volume = std::stod(volumeStr);

        bars_.push_back(bar);
    }

    if (bars_.empty()) {
        throw std::runtime_error("No data rows found in file");
    }

}