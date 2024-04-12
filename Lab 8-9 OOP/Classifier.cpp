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
string NNClassifier::classify(const std::vector<DataPoint>& data, const DataPoint& samplePoint) {
    double minDistance = numeric_limits<double>::max();
    int predictedLabel = -1;
    string result;

    for (const auto& point : data) {
        double distance = calculateDistance(samplePoint.x, samplePoint.y, samplePoint.z, point.x, point.y, point.z);
        if (distance < minDistance) {
            minDistance = distance;
            predictedLabel = point.label;
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

// AnotherClassifier
string AnotherClassifier::classify(const std::vector<DataPoint>& trainingData, const DataPoint& samplePoint) {
    string AnotherClassifierString = "";
    return AnotherClassifierString;
}

// KNNClassifier
string KNNClassifier::classify(const std::vector<DataPoint>& trainingData, const DataPoint& samplePoint) {
    string KNNClassifierString = "";
    return KNNClassifierString;
}

vector<DataPoint> readData(const string& filename, bool hasLabels) {
    vector<DataPoint> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Cannot open this file: " << filename << endl;
        return data; // Return an empty vector to signal an error
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        istringstream issLine(line);
        string value;
        double x, y, z;
        int label = -1; // Default label if not provided
        char comma;

        getline(issLine, value, ',');
        x = stod(value);
        getline(issLine, value, ',');
        y = stod(value);
        getline(issLine, value, hasLabels ? ',' : '\n');
        z = stod(value);

        if (hasLabels) {
            getline(issLine, value);
            label = stoi(value);
        }

        data.push_back({ x, y, z, label });
    }

    file.close();
    return data;
}

// Function to interact with the user and perform classification
void interact(Classifier* classifier, const vector<DataPoint>& trainingData) {
    // Check if the classifier is NNClassifier to provide options
    /*NNClassifier* nnClassifier = dynamic_cast<NNClassifier*>(classifier);*/
    if (auto nnClassifier = dynamic_cast<NNClassifier*>(classifier)) {
        cout << "Choose an option:" << endl;
        cout << "1. Enter sample data (x, y, z)" << endl;
        cout << "2. Enter a data file name" << endl;

        int option;
        cin >> option;

        switch (option) {
        case 1: {
            double inputX, inputY, inputZ;
            cout << "Enter x, y, z coordinates of the gravity vector: ";
            cin >> inputX >> inputY >> inputZ;
            DataPoint samplePoint = { inputX, inputY, inputZ, -1 }; // -1 as a dummy label
            string result1 = nnClassifier->classify(trainingData, samplePoint);
            cout << result1 << endl;
            break;
        }
        case 2: {
            string dataFileName;
            cout << "Enter data file name: ";
            cin >> dataFileName;
            vector<DataPoint> fileData = readData(dataFileName, false); // false indicates no labels
            ofstream resultFile("results.txt");

            if (!fileData.empty() && resultFile.is_open()) {
                for (const auto& samplePoint : fileData) {
                    // Classify and get the result as a string
                    string result = nnClassifier->classify(trainingData, samplePoint);

                    // Print to console
                    cout << result << endl;

                    // Write to file
                    resultFile << result << endl;
                }
                resultFile.close();
            }
            else {
                if (fileData.empty()) {
                    cerr << "No data to classify. Please check the file and try again." << endl;
                }
                if (!resultFile.is_open()) {
                    cerr << "Could not open results.txt for writing." << endl;
                }
            }
            break;
        }
        default:
            cout << "Invalid option" << endl;
        }
    }
    else if (auto anotherClassifier = dynamic_cast<AnotherClassifier*>(classifier)) {
        // Interaction for AnotherClassifier
        cout << "Using AnotherClassifier" << endl;
        // You can add more code here if AnotherClassifier needs to perform any actions
    }
    else if (auto knnClassifier = dynamic_cast<KNNClassifier*>(classifier)) {
        // Interaction for KNNClassifier
        cout << "Using KNNClassifier" << endl;
        // You can add more code here if KNNClassifier needs to perform any actions
    }
    else {
        cout << "Classifier type not recognized. Exiting the program." << endl;
        exit(1);
    }
}