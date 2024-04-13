#include "NNClassifier.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>


double NNClassifier::calculateDistance(const DataPoint& a, const DataPoint& b) {
    return std::sqrt(std::pow(a.getX() - b.getX(), 2) + std::pow(a.getY() - b.getY(), 2) + std::pow(a.getZ() - b.getZ(), 2));
}

// Nearest Neighbor Classifier
std::string NNClassifier::classify(const std::vector<DataPoint>& trainingData, const DataPoint& samplePoint) {
    double minDistance = std::numeric_limits<double>::max();
    int predictedLabel = -1;
    std::string result;

    for (const auto& point : trainingData) {
        double distance = calculateDistance(samplePoint, point);
        if (distance < minDistance) {
            minDistance = distance;
            predictedLabel = point.getLabel();
        }
    }

    // Output the predicted label
    switch (predictedLabel) {
    case 1:
        result = "Face up";
        break;
    case 2:
        result = "Face down";
        break;
    case 3:
        result = "Portrait";
        break;
    case 4:
        result = "Portrait upside down";
        break;
    case 5:
        result = "Landscape left";
        break;
    case 6:
        result = "Landscape right";
        break;
    default:
        result = "Unknown orientation";
    }
    return result;
}