#pragma once
#include "Classifier.h"

class KNNClassifier : public Classifier {
public:
    std::string classify(const std::vector<DataPoint>& trainingData, const DataPoint& samplePoint) override;
};