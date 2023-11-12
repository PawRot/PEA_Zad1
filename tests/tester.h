//
// Created by Michał Zychowicz on 12/11/2023.
//

#ifndef PEA_ZAD1_TESTER_H
#define PEA_ZAD1_TESTER_H

#include <chrono>
#include <vector>
#include <future>
#include <thread>

#include "../algorithms/BranchBoundNode.h"
#include "../data/fileOperator.h"
#include "../data/dataGenerator.h"
#include "../algorithms/bruteForce.h"
#include "../algorithms/BranchBound.h"


class tester {
public:
    tester();
    ~tester();
    static void maxProblemSizeBruteForce(const int& maxTimeSeconds);

    template<typename T>
    static void maxProblemSizeBranchBound(const int& maxTimeSeconds, const std::string &type);

};


#endif //PEA_ZAD1_TESTER_H
