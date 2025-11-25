#pragma once

#include <vector>
#include <string>
#include "Bar.h"

class DataFeed {
public:
    explicit DataFeed(const std::string& filePath);

    bool hasNext() const;
    const Bar& next();


private:
    std::vector<Bar> bars_;
    std::size_t currentIndex_{0};

    void loadFakeData();
    void loadFromCsv(const std::string& filePath);
};