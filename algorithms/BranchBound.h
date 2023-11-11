

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

    std::atomic_bool isRunning;

private:
    std::vector<std::vector<int>> dataMatrix;

    struct Node {
        int level;
        int lowerBound;
        std::vector<int> path;
    };

    struct compareNodes {
        bool operator()(const Node &node1, const Node &node2) {
            return node1.lowerBound > node2.lowerBound;
        }
    };


    std::priority_queue<Node, std::deque<Node>, compareNodes> priorityQueue;
    unsigned long numberOfCities;
    std::vector<int> bestPathIndexes; // indexes of best path
    int bestUpperBound; // current best path length
    std::vector<int> smallestValueRow, smallestValueColumn;

    void calculateLowerBound(Node &node);




};


#endif //PEA_ZAD1_BRANCHBOUND_H
