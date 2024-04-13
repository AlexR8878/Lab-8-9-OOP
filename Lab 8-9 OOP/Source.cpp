#include <iostream>
#include "Classifier.h"
#include "DataPoint.h"
#include "Utility.h"

using namespace std;

int main() {
    vector<DataPoint> data = readData("trainingData.txt", true);

    // Instantiate the classifiers
    Classifier* nnClassifier = new NNClassifier();
    Classifier* anotherClassifier = new AnotherClassifier();
    Classifier* knnClassifier = new KNNClassifier();

    // Prompt the user to choose a classifier
    cout << "Choose a classifier:" << endl;
    cout << "1) Nearest Neighbor (NN) Classifier" << endl;
    cout << "2) Another Classifier" << endl;
    cout << "3) KNN Classifier" << endl;

    int choice;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        interact(nnClassifier, data);
        break;
    case 2:
        interact(anotherClassifier, data);
        break;
    case 3:
        interact(knnClassifier, data);
        break;
    default:
        cout << "Invalid choice" << endl;
    }

    // Deallocate memory
    delete nnClassifier;
    delete anotherClassifier;
    delete knnClassifier;

    return 0;
}