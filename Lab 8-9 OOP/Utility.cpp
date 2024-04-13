#include "Utility.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

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

        DataPoint point;
        point.setX(x);
        point.setY(y);
        point.setZ(z);
        point.setLabel(label);
        data.push_back(point);
    }

    file.close();
    return data;
}

void interact(Classifier* classifier, const vector<DataPoint>& trainingData) {
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
            DataPoint samplePoint;
            samplePoint.setX(inputX);
            samplePoint.setY(inputY);
            samplePoint.setZ(inputZ);
            samplePoint.setLabel(-1); // -1 as a dummy label
            string result = nnClassifier->classify(trainingData, samplePoint);
            cout << result << endl;
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
                    string result = nnClassifier->classify(trainingData, samplePoint);
                    resultFile << samplePoint.getX() << "," << samplePoint.getY() << "," << samplePoint.getZ() << "," << result << endl;
                    cout << samplePoint.getX() << "," << samplePoint.getY() << "," << samplePoint.getZ() << "," << result << endl;
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
        cout << "Using AnotherClassifier (Not Yet Implemented)" << endl;
        // Additional code for AnotherClassifier can be added here
    }
    else if (auto knnClassifier = dynamic_cast<KNNClassifier*>(classifier)) {
        cout << "Using KNNClassifier (Not Yet Implemented)" << endl;
        // Additional code for KNNClassifier can be added here
    }
    else {
        cout << "Classifier type not recognized. Exiting the program." << endl;
        exit(1);
    }
}