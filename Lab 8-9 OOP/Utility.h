#pragma once
#include <vector>
#include "DataPoint.h"
#include "Classifier.h"
#include "NNClassifier.h"
#include "KNNClassifier.h"
#include "AnotherClassifier.h"

std::vector<DataPoint> readData(const std::string& filename, bool hasLabels);
void interact(Classifier* classifier, const std::vector<DataPoint>& data);