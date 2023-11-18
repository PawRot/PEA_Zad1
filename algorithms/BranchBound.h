

#ifndef PEA_ZAD1_BRANCHBOUND_H
#define PEA_ZAD1_BRANCHBOUND_H

#include <queue>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include <atomic>
#include <stack>

#include "BranchBoundNode.h"

#include <iostream>

template<typename T>
class BranchBound {

public:
    explicit BranchBound(const std::vector<std::vector<int>> &matrix);

    ~BranchBound();

    std::tuple<int, std::vector<int>, std::chrono::duration<float>> branchBoundAlgorithm();

    // atomic boolean for testing max N for set execution time
    std::atomic_bool isRunning;


private:
    // matrix that contains data
    std::vector<std::vector<int>> dataMatrix;

    // queue can either be a priority queue for best first or Stack for DFS
    T queue;
    unsigned long numberOfCities;
    std::vector<int> bestPathIndexes; // indexes of best path
    int bestBound; // current best path length and upper bound


    void calculateLowerBound(Node &node) const;

    void calculateLeafBound(Node &node) const;

    void calculateRootBound(Node &node) const;

};


#endif //PEA_ZAD1_BRANCHBOUND_H
