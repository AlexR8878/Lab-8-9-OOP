#include "Classifier.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// Function to calculate the Euclidean distance between two points
double NNClassifier::calculateDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

// Nearest Neighbor Classifier
void NNClassifier::classify(const vector<DataPoint>& data) {
    // Interact with the user to get input data
    double inputX, inputY, inputZ;
    cout << "Enter x, y, z coordinates of the gravity vector: ";
    cin >> inputX >> inputY >> inputZ;

    // Find the nearest neighbor
    double minDistance = numeric_limits<double>::max();
    int predictedLabel = -1;

    for (const auto& point : data) {
        double distance = calculateDistance(inputX, inputY, inputZ, point.x, point.y, point.z);
        if (distance < minDistance) {
            minDistance = distance;
            predictedLabel = point.label;
        }
    }

    // Output the predicted label
    switch (predictedLabel) {
    case 1:
        cout << "Face up" << endl;
        break;
    case 2:
        cout << "Face down" << endl;
        break;
    case 3:
        cout << "Portrait" << endl;
        break;
    case 4:
        cout << "Portrait upside down" << endl;
        break;
    case 5:
        cout << "Landscape left" << endl;
        break;
    case 6:
        cout << "Landscape right" << endl;
        break;
    default:
        cout << "Unknown orientation" << endl;
    }
}

// AnotherClassifier
void AnotherClassifier::classify(const vector<DataPoint>& data) {
    cout << "Using AnotherClassifier" << endl;
}

// KNNClassifier
void KNNClassifier::classify(const vector<DataPoint>& data) {
    cout << "Using KNNClassifier" << endl;
}

vector<DataPoint> readData(const string& filename) {
    vector<DataPoint> data;
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue; // Skip empty lines

            istringstream issLine(line);
            string value;
            double x, y, z;
            int label;
            char comma;

            // Read the x coordinate
            getline(issLine, value, ',');
            x = stod(value);

            // Read the y coordinate
            getline(issLine, value, ',');
            y = stod(value);

            // Read the z coordinate
            getline(issLine, value, ',');
            z = stod(value);

            // Read the label
            getline(issLine, value);
            label = stoi(value);

            // Add the data point to the vector
            data.push_back({ x, y, z, label });
        }
        file.close();
    }
    else {
        cout << "Cannot open this file: " << filename << endl;
    }

    return data;
}

// Function to interact with the user and perform classification
void interact(Classifier* classifier, const vector<DataPoint>& data) {
    classifier->classify(data);
}