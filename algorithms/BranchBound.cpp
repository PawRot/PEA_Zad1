

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
    auto start = std::chrono::steady_clock::now();
    Node root;
    root.level = 0;
    root.path = path;
    root.lowerBound = calculateLowerBound(root);
    priorityQueue.push(root);

    while (!priorityQueue.empty()) {
        Node node = priorityQueue.top();
        priorityQueue.pop();
        if (node.lowerBound < bestUpperBound) {
            for (int i = 1; i < numberOfCities; i++) {
                if (std::find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                    Node newNode;
                    newNode.level = node.level + 1;
                    newNode.path = node.path;
                    newNode.path[newNode.level] = i;
                    if (newNode.level == numberOfCities - 2) {
                        for (int j = 1; j < numberOfCities; j++) {
                            if (std::find(newNode.path.begin(), newNode.path.end(), j) == newNode.path.end()) {
                                newNode.path[newNode.level + 1] = j;
                                newNode.path[newNode.level + 2] = 0;
                                newNode.lowerBound = calculateLowerBound(newNode);
                                if (newNode.lowerBound < bestUpperBound) {
                                    bestUpperBound = newNode.lowerBound;
                                    bestPathIndexes = newNode.path;
                                }
                            }
                        }
                    } else {
                        newNode.lowerBound = calculateLowerBound(newNode);
                        if (newNode.lowerBound < bestUpperBound) {
                            priorityQueue.push(newNode);
                        }
                    }
                }
            }
        }
    }
    return {bestUpperBound, bestPathIndexes, 0};
}

int BranchBound::calculateLowerBound(const Node &node) {
    int lowerBound = 0;
    int currentPath = 0;
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for (int i = 0; i < node.level; i++) {
        currentPath += dataMatrix[node.path[i]][node.path[i + 1]];
    }
    for (int i = node.level + 1; i < numberOfCities; i++) {
        min1 = std::min(min1, dataMatrix[node.path[node.level]][i]);
        min2 = std::min(min2, dataMatrix[i][0]);
    }
    lowerBound = currentPath + min1 + min2;
    return lowerBound;
}
