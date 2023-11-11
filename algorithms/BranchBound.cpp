

#include "BranchBound.h"

BranchBound::BranchBound(const std::vector<std::vector<int>> &matrix)
        : dataMatrix(matrix), numberOfCities(matrix.size()), bestUpperBound(INT_MAX), isRunning(true) {
    bestPathIndexes.resize(numberOfCities);
}

BranchBound::~BranchBound() = default;

std::tuple<int, std::vector<int>, long long> BranchBound::branchBoundAlgorithm() {


    auto start = std::chrono::steady_clock::now();
    // Find the smallest value in each row and column
//    for (int i = 0; i < numberOfCities; ++i) {
//        // Find smallest value in row, do not include number in position equal to i
//        std::vector<int> row;
//        row.reserve(numberOfCities);
//        for (int j = 0; j < numberOfCities; ++j) {
//            if (j != i) {
//                row.push_back(dataMatrix[i][j]);
//            }
//        }
//        smallestValueRow.push_back(*std::min_element(row.begin(), row.end()));
//
//    }

//     print smallestValueRow
//     for (int i = 0; i < numberOfCities; ++i) {
//         std::cout << smallestValueRow[i] << " ";
//     }
//    std::cout << std::endl;

//    for (int i = 0; i < numberOfCities; ++i) {
//        std::vector<int> column;
//        column.reserve(numberOfCities);
//        for (int j = 0; j < numberOfCities; ++j) {
//            if (j != i) {
//                column.push_back(dataMatrix[j][i]);
//            }
//        }
//        smallestValueColumn.push_back(*std::min_element(column.begin(), column.end()));
//    }
    // print smallestValueColumn
//     for (int i = 0; i < numberOfCities; ++i) {
//         std::cout << smallestValueColumn[i] << " ";
//     }
//     std::cout << std::endl;


    // Initialize priority queue
    Node root{0, 0, {0}};
    calculateLowerBound(root);
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
//                childNode.lowerBound = node.lowerBound + dataMatrix[node.path[node.level]][i];
                if (childNode.level == numberOfCities - 1) {
                    childNode.lowerBound += dataMatrix[childNode.path[childNode.level]][0];
//                    calculateLowerBound(childNode);
                } else {
                    calculateLowerBound(childNode);
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


void BranchBound::calculateLowerBound(Node &node) {
    int lowerBound = 0;

    // calculate lower bound of first node
    if (node.level == 0) {
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
        // calculate lower bound of other nodes
    } else {
        // find minimum value in each row and add it to lowerBound
        // calculate value of current path
        for (int i = 0; i < node.level; ++i) {
            lowerBound += dataMatrix[node.path[i]][node.path[i + 1]];
        }
        // find minimum value of rows that are not included in current path, always include possible path to 0
        for (int i = 0; i < numberOfCities; ++i) {
            if ((std::find(node.path.begin(), node.path.end()-1, i) == node.path.end())) {
                // Find the smallest value in row, do not include number in position equal to i
                std::vector<int> row;
                row.reserve(numberOfCities);
                for (int j = 0; j < numberOfCities; ++j) {
                    // do not include number in position equal to i
                    // do not include paths that are already in current path
                    // if i is equal to last element of node.path, include path to 0
                    if ((j != i && (std::find(node.path.begin(), node.path.end()-1, j) == node.path.end())) || (i == node.path[node.level] && (j == 0))) {
                        row.push_back(dataMatrix[i][j]);
                    }

                }
                lowerBound += *std::min_element(row.begin(), row.end());
            }
        }
        node.lowerBound = lowerBound;
    }

    return;
}

