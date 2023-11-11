

#include "BranchBound.h"

BranchBound::BranchBound(const std::vector<std::vector<int>> &matrix)
        : dataMatrix(matrix), numberOfCities(matrix.size()), bestBound(INT_MAX), isRunning(true) {
    bestPathIndexes.resize(numberOfCities);
}

BranchBound::~BranchBound() = default;

std::tuple<int, std::vector<int>, long long> BranchBound::branchBoundAlgorithm() {


    auto start = std::chrono::steady_clock::now();



    // Initialize priority queue
    Node root{0, {0}};
    calculateRootBound(root);
    priorityQueue.push(root);

    while (!priorityQueue.empty()) {
        Node node = priorityQueue.top();
        priorityQueue.pop();


        if (node.lowerBound < bestBound) {

            for (int i = 0; i < numberOfCities; ++i) {
                if (std::find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                    Node childNode;
                    childNode.path = node.path;
                    childNode.path.push_back(i);
//                    for (int k : childNode.path) {
//                        std::cout << k << " ";
//                    }
//                    std::cout << std::endl;
//                childNode.lowerBound = node.lowerBound;// + dataMatrix[node.path[node.level]][i];
                    if (childNode.path.size() == numberOfCities) {
                        childNode.path.push_back(0);
                        calculateLeafBound(childNode);
                        if (childNode.lowerBound < bestBound) {
                            bestBound = childNode.lowerBound;
                            bestPathIndexes = childNode.path;
                        }
                        for (int k : childNode.path) {
                            std::cout << k << " ";
                        }
                        std::cout << " - " << childNode.lowerBound << " - Full path";
                        std::cout << std::endl;

//                    childNode.lowerBound = node.lowerBound;
//                    childNode.lowerBound += dataMatrix[childNode.path[childNode.path.size() - 1]][0];
//                    calculateLowerBound(childNode);
                    } else {
                        calculateLowerBound(childNode);
                        if (childNode.lowerBound < bestBound) {
                            priorityQueue.push(childNode);
                            for (int k : childNode.path) {
                                std::cout << k << " ";
                            }
                            std::cout << " - " << childNode.lowerBound;
                            std::cout << std::endl;

                        }
                    }


                }
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return {bestBound, bestPathIndexes, duration};
}


void BranchBound::calculateLowerBound(Node &node) {
    int lowerBound = 0;
    // find the lowerBound for partial path
    // calculate value of current path
    for (int i = 0; i < node.path.size(); i++) {
        lowerBound += dataMatrix[node.path[i]][node.path[i + 1]];
    }
    if (node.path.size() == numberOfCities) {
        node.lowerBound = lowerBound;
        return;
    }
    // for last vertex in current path, consider path values from it to vertexes not in path, for vertexes not in path also consider path to vertex 0
    for (int i = 0; i < numberOfCities; i++) {
        // if vertex not in path, excluding last element
        if (std::find(node.path.begin(), node.path.end() - 1, i) == node.path.end()) {
            std::vector<int> row;
            row.reserve(numberOfCities);
            for (int j = 0; j < numberOfCities; j++) {
                if (i != j) {
                    if (i == node.path[node.path.size() - 1] &&
                        (std::find(node.path.begin(), node.path.end(), j) == node.path.end())) {
                        row.push_back(dataMatrix[i][j]);
                    } else if (std::find(node.path.begin() + 1, node.path.end(), j) == node.path.end()) {
                        row.push_back(dataMatrix[i][j]);
                    }
                }
            }
            lowerBound += *std::min_element(row.begin(), row.end());
        }
    }

    node.lowerBound = lowerBound;
}

void BranchBound::calculateLeafBound(Node &node) {
    int lowerBound = 0;
    for (int i = 0; i < node.path.size(); i++) {
        lowerBound += dataMatrix[node.path[i]][node.path[i+1]];
    }
    node.lowerBound = lowerBound;
}

void BranchBound::calculateRootBound(BranchBound::Node &node) {
    // calculate lower bound of root node
    int lowerBound = 0;
    // find minimum value in each row and add it to lowerBound
    for (int i = 0; i < numberOfCities; ++i) {
        // Find the smallest value in row, do not include number in position equal to i
        std::vector<int> row;
        row.reserve(numberOfCities);
        for (int j = 0; j < numberOfCities; ++j) {
            if (j != i) {
                row.push_back(dataMatrix[i][j]);
            }
        }
        lowerBound += *std::min_element(row.begin(), row.end());
    }
    node.lowerBound = lowerBound;

}

