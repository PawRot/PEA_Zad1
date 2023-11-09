

#include "BranchBound.h"

BranchBound::BranchBound(const std::vector<std::vector<int>> &matrix) {
    this->dataMatrix = matrix;
    this->numberOfCities = static_cast<int>(matrix.size());
    this->bestUpperBound = INT_MAX;
    this->isRunning = true;
    this->citiesIndexes.resize(numberOfCities);
    std::iota(citiesIndexes.begin(), citiesIndexes.end(), 0);
    this->path.resize(numberOfCities + 1);
    this->bestPathIndexes.resize(numberOfCities + 1);
    this->bestPathIndexes[numberOfCities] = 0;
    this->path[numberOfCities] = 0;
    this->path[0] = 0;
    this->bestPathIndexes[0] = 0;
}

BranchBound::~BranchBound() = default;

std::tuple<int, std::vector<int>, long long> BranchBound::branchBoundAlgorithm() {

    Node root;
    root.level = 0;
    root.path = path;
    root.path[0] = 0;
    root.path[1] = 0;
    root.prevCity = 0;
    root.cost = 0;
    root.bound = calculateLowerBound(root);
    priorityQueue.push(root);

    do {
        Node node = priorityQueue.top();
        priorityQueue.pop();
        if (node.bound < bestUpperBound) {
            for (int i = 1; i < numberOfCities; i++) {
                if (node.path[i] == -1) {
                    continue;
                }
                Node newNode;
                newNode.level = node.level + 1;
                newNode.path = node.path;
                newNode.path[node.level + 1] = -1;
                newNode.path[node.level] = citiesIndexes[i];
                newNode.prevCity = citiesIndexes[i];
                newNode.cost = node.cost + dataMatrix[node.prevCity][citiesIndexes[i]];
                if (newNode.level == numberOfCities - 2) {
                    newNode.cost += dataMatrix[citiesIndexes[i]][0];
                }
                newNode.bound = calculateLowerBound(newNode);
                if (newNode.bound < bestUpperBound) {
                    priorityQueue.push(newNode);
                }
            }
        }
    } while (!priorityQueue.empty());


    return {bestUpperBound, bestPathIndexes, 0};
}

int BranchBound::calculateLowerBound(const Node &node) {
    int lowerBound = 0;
    int min;
    int sum = 0;
    for (int i = 0; i < numberOfCities; i++) {
        min = INT_MAX;
        for (int j = 0; j < numberOfCities; j++) {
            if (dataMatrix[i][j] < min && i != j) {
                min = dataMatrix[i][j];
            }
        }
        if (min != INT_MAX) {
            lowerBound += min;
        }
    }
    for (int i = 0; i <= node.level; i++) {
        sum += dataMatrix[node.path[i]][node.path[i + 1]];
    }
    lowerBound += sum;
    return lowerBound;
}
