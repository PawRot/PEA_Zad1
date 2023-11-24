#include <chrono>
#include "BranchBound.h"

template<typename T>
BranchBound<T>::BranchBound(const std::vector<std::vector<int>>&matrix)
    : dataMatrix(matrix), numberOfCities(matrix.size()), bestBound(INT_MAX), isRunning(true) {
    bestPathIndexes.resize(numberOfCities);
}

template<typename T>
BranchBound<T>::~BranchBound() = default;

template<typename T>
std::tuple<int, std::vector<int>, std::chrono::duration<float>> BranchBound<T>::branchBoundAlgorithm() {
    const auto start = std::chrono::steady_clock::now();

    std::vector<int> citiesIndexes;
    citiesIndexes.reserve(numberOfCities - 1);
    for (int i = 1; i < numberOfCities; ++i) {
        citiesIndexes.push_back(i);
    }

    // Initialize priority queue
    Node root{0, {0}};
    calculateRootBound(root);

    // root.notVisited.resize(numberOfCities - 1);
    // std::generate(root.notVisited.begin(), root.notVisited.end(), [n = 1]() mutable { return n++; });

    queue.push(root);


    // execute while queue is not empty
    while (!queue.empty()) {
        // get node from top of queue and remove it
        Node node = queue.top();
        queue.pop();

        // check if node can lead to better solution
        if (node.lowerBound < bestBound) {
            std::list<int> notVisited;
            notVisited.resize(numberOfCities - node.path.size());
            std::copy_if(citiesIndexes.begin(), citiesIndexes.end(), std::back_inserter(notVisited),
                         [&node](const int cityIndex) {
                             return std::find(node.path.begin(), node.path.end(), cityIndex) == node.path.end();
                         });
            for (auto i: notVisited) {
                // go over cities not in path

                // create child node, copy parent path and push new city to back
                Node childNode;
                childNode.path = node.path;
                childNode.path.push_back(i);
                std::list<int> notVisitedCopy = notVisited;
                notVisitedCopy.erase(std::ranges::find(notVisitedCopy, i));
//                childNode.notVisited = node.notVisited;
//                childNode.notVisited.erase(std::ranges::find(childNode.notVisited, i));


                // if all cities all already in path, add starting city to path and calculate leaf bound
                if (notVisitedCopy.empty()) {
                    childNode.path.push_back(0);
                    calculateLeafBound(childNode);
                    // if leaf path is lower than bestBound then set bestBound to it and change best path
                    if (childNode.lowerBound < bestBound) {
                        bestBound = childNode.lowerBound;
                        bestPathIndexes = childNode.path;
                    }
                }
                else {
                    // calculate lowerBound of node, and if it's lower than bestBound, add it to the queue
                    calculateLowerBound(childNode);
                    if (childNode.lowerBound < bestBound) {
                        queue.push(childNode);
                    }

#ifdef testEnable // if testEnable is defined, this code will be compiled
                    if (!isRunning) {
                        std::cout << "Algorithm stopped" << std::endl;
                        throw std::runtime_error("Algorithm stopped");
                    }

                    //                        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() > 5) {
                    //                            std::cout << "Algorithm stopped" << std::endl;
                    //                            throw std::runtime_error("Algorithm exceeded set time");
                    //                        }
#endif
                }
            }
        }
    }
    const auto end = std::chrono::steady_clock::now();
    const auto executionTime = end - start;
    return {bestBound, bestPathIndexes, executionTime};
}

template<typename T>
void BranchBound<T>::calculateLowerBound(Node&node) const {
    int lowerBound = 0;
    // find the lowerBound for partial path
    // calculate value of cities in current path
    for (int i = 0; i < node.path.size() - 1; i++) {
        lowerBound += dataMatrix[node.path[i]][node.path[i + 1]];
    }


    std::vector<int> row;
    row.reserve(numberOfCities);

    for (const auto i: notVisited) {
        row.push_back(dataMatrix[node.path[node.path.size() - 1]][i]);
    }
    lowerBound += *std::ranges::min_element(row);


    row.clear();


    // for last city in current path, consider path values from it to cities not in path, for cities not in path also consider path to city 0
    for (const auto i: node.notVisited) {
        // if vertex not in path, excluding last element
        row.reserve(numberOfCities);
        for (const auto j: node.notVisited) {
            if (i != j) {
                row.push_back(dataMatrix[i][j]);
            }
        }
        row.push_back(dataMatrix[i][0]);
        lowerBound += *std::ranges::min_element(row);
        row.clear();
    }

    node.lowerBound = lowerBound;
}

template<typename T>
void BranchBound<T>::calculateLeafBound(Node&node) const {
    // calculate distance between all cities in path
    int lowerBound = 0;
    for (int i = 0; i < node.path.size() - 1; ++i) {
        lowerBound += dataMatrix[node.path[i]][node.path[i + 1]];
    }
    node.lowerBound = lowerBound;
}

template<typename T>
void BranchBound<T>::calculateRootBound(Node&node) const {
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
        lowerBound += *std::ranges::min_element(row);
    }
    node.lowerBound = lowerBound;
}

// template is limited to using stack or priority queue
template class BranchBound<std::stack<Node>>;
//template class BranchBound<std::priority_queue<Node, std::vector<Node>, compareNodes>>;
template class BranchBound<nodePriorityQueue>;
