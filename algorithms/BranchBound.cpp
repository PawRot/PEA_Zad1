

#include "BranchBound.h"

BranchBound::BranchBound(const std::vector<std::vector<int>> &matrix)
        : dataMatrix(matrix), numberOfCities(matrix.size()), bestUpperBound(INT_MAX), isRunning(true) {
    bestPathIndexes.resize(numberOfCities);
}

BranchBound::~BranchBound() = default;

std::tuple<int, std::vector<int>, long long> BranchBound::branchBoundAlgorithm() {


    auto start = std::chrono::steady_clock::now();
    // Find the smallest value in each row and column
    for (int i = 0; i < numberOfCities; ++i) {
        // Find smallest value in row, do not include number in position equal to i
        std::vector<int> row;
        row.reserve(numberOfCities);
        for (int j = 0; j < numberOfCities; ++j) {
            if (j != i) {
                row.push_back(dataMatrix[i][j]);
            }
        }
        smallestValueRow.push_back(*std::min_element(row.begin(), row.end()));

    }

//     print smallestValueRow
//     for (int i = 0; i < numberOfCities; ++i) {
//         std::cout << smallestValueRow[i] << " ";
//     }
//    std::cout << std::endl;

    for (int i = 0; i < numberOfCities; ++i) {
        std::vector<int> column;
        column.reserve(numberOfCities);
        for (int j = 0; j < numberOfCities; ++j) {
            if (j != i) {
                column.push_back(dataMatrix[j][i]);
            }
        }
        smallestValueColumn.push_back(*std::min_element(column.begin(), column.end()));
    }
    // print smallestValueColumn
//     for (int i = 0; i < numberOfCities; ++i) {
//         std::cout << smallestValueColumn[i] << " ";
//     }
//     std::cout << std::endl;


    // Initialize priority queue
    Node root{0, 0, {0}};
    root.lowerBound = calculateLowerBound(root);
    priorityQueue.push(root);

    while (!priorityQueue.empty()) {
        Node node = priorityQueue.top();
        priorityQueue.pop();

        if (node.level == numberOfCities - 1) {
            node.path.push_back(0);
            if (node.lowerBound < bestUpperBound) {
                bestPathIndexes = node.path;
                bestUpperBound = node.lowerBound;
            }
            continue;
        }

        for (int i = 0; i < numberOfCities; ++i) {
            if (std::find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                Node childNode;
                childNode.path = node.path;
                childNode.path.push_back(i);
                childNode.level = node.level + 1;
                childNode.lowerBound = node.lowerBound + dataMatrix[node.path[node.level]][i];
                if (childNode.level == numberOfCities - 1) {
                    childNode.lowerBound += dataMatrix[childNode.path[childNode.level]][0];
                } else {
                    childNode.lowerBound += calculateLowerBound(childNode);
                }

                if (childNode.lowerBound < bestUpperBound) {
                    priorityQueue.push(childNode);
                }
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return {bestUpperBound, bestPathIndexes, duration};
}

int BranchBound::calculateLowerBound(const Node &node) {
    int lowerBound = 0;
    for (int i = 0; i < numberOfCities; ++i) {
        if (std::find(node.path.begin(), node.path.end(), i) == node.path.end()) {
            lowerBound += smallestValueRow[i];
        }
    }
    return lowerBound;
}

bool BranchBound::findNonNegative(int a, int b) {
    if (a < 0) a = std::numeric_limits<int>::max();
    if (b < 0) b = std::numeric_limits<int>::max();
    return a < b;
}
