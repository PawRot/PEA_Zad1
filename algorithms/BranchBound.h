

#ifndef PEA_ZAD1_BRANCHBOUND_H
#define PEA_ZAD1_BRANCHBOUND_H

#include <queue>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include <atomic>

#include <iostream>

class BranchBound {

public:
    explicit BranchBound(const std::vector<std::vector<int>> &matrix);

    ~BranchBound();

    std::tuple<int, std::vector<int>, long long> branchBoundAlgorithm();

    // atomic boolean for testing max N for set execution time
    std::atomic_bool isRunning;

private:
    // matrix that contains data
    std::vector<std::vector<int>> dataMatrix;

    // node struct
    struct Node {
        int lowerBound;
        std::vector<int> path;
    };

    // custom compare
    struct compareNodes {
        bool operator()(const Node &node1, const Node &node2) {
            return node1.lowerBound > node2.lowerBound;
        }
    };

    // priority queue using vector as container
    std::priority_queue<Node, std::vector<Node>, compareNodes> priorityQueue;
    unsigned long numberOfCities;
    std::vector<int> bestPathIndexes; // indexes of best path
    int bestBound; // current best path length


    void calculateLowerBound(Node &node);

    void calculateLeafBound(Node &node);

    void calculateRootBound(Node &node);

};


#endif //PEA_ZAD1_BRANCHBOUND_H
