#pragma once
#include "Classifier.h"

class NNClassifier : public Classifier {
public:
    std::string classify(const std::vector<DataPoint>& trainingData, const DataPoint& samplePoint) override;
private:
    double calculateDistance(const DataPoint& a, const DataPoint& b);
};