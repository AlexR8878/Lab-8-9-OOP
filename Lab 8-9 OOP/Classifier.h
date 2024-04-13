#pragma once
#include <vector>
#include <string>
#include "DataPoint.h"

class Classifier {
public:
    virtual std::string classify(const std::vector<DataPoint>& trainingData, const DataPoint& samplePoint) = 0;
    virtual ~Classifier() {}
};