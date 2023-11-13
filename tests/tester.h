
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

    static void testBruteForce(const int &N);

    template<typename T>
    static void testBranchBound(const int &N, const int& maxTimeSeconds, const std::string &type);


private:
    template<typename T>
    static std::tuple<bool, int> runBranchBound(const std::vector<std::vector<int>> &testData, const int &maxTimeSeconds, std::vector<long long> &result, int &failedTries);

};


#endif //PEA_ZAD1_TESTER_H
