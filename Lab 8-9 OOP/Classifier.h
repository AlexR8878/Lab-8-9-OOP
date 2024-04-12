#pragma once
#include <vector>
#include <string>
#include <iostream>

// Define a structure to hold the gravity vector and its corresponding label
struct DataPoint {
    double x;
    double y;
    double z;
    int label;
};

// Abstract base class for classifiers
class Classifier {
public:
    virtual void classify(const std::vector<DataPoint>& data) = 0;
    virtual ~Classifier() {} // Make the destructor virtual
};

// Nearest Neighbor Classifier
class NNClassifier : public Classifier {
public:
    void classify(const std::vector<DataPoint>& data) override;

private:
    // Function to calculate the Euclidean distance between two points
    double calculateDistance(double x1, double y1, double z1, double x2, double y2, double z2);
};

// AnotherClassifier
class AnotherClassifier : public Classifier {
public:
    void classify(const std::vector<DataPoint>& data) override;
};

// KNNClassifier
class KNNClassifier : public Classifier {
public:
    void classify(const std::vector<DataPoint>& data) override;
};

// Function to read data from a text file
std::vector<DataPoint> readData(const std::string& filename);

// Function to interact with the user and perform classification
void interact(Classifier* classifier, const std::vector<DataPoint>& data);

