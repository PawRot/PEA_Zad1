//
// Created by Michał Zychowicz on 12/11/2023.
//

#include "tester.h"

tester::tester() = default;

tester::~tester() = default;

void tester::maxProblemSizeBruteForce(const int &maxTimeSeconds) {

    int tries = 0, failedTries = 0;
    bool success = false;
    int N = 2;

    while (true) {

        auto testData = dataGenerator::generateTestData(N, 10, 9999);

        bruteForce bruteForce(testData);

        auto promise = std::async(std::launch::async, &bruteForce::bruteForceAlgorithm, &bruteForce);

        std::chrono::seconds span(maxTimeSeconds);
        if (promise.wait_for(span) == std::future_status::timeout) {
            std::cout << "Algorithm exceeded set time" << std::endl;
            bruteForce.isRunning = false;
            failedTries++;
        }
        try {
            auto resultTuple = promise.get();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::get<2>(resultTuple)).count();
            std::cout << "Algorithm finished in " << duration << "milliseconds" << std::endl;
            success = true;
        } catch (std::runtime_error &e) {
        }

        std::cout << failedTries << std::endl;
        if (success) {
            N++;
            success = false;
            failedTries = 0;
        } else if (failedTries >= 3) {
            std::vector<long long> result;
            result.push_back(N - 1);
            fileOperator::saveResultFile("bruteForceMaxN.csv", result);
            return;
        }
    }
}

template<typename T>
void tester::maxProblemSizeBranchBound(const int &maxTimeSeconds, const std::string &type) {

    std::vector<long long> result;
    int failedTries = 0;
    bool success = false;
    int N = 10;

    while (true) {

        auto testData = dataGenerator::generateTestData(N, 10, 9999);

        BranchBound<T> branchBound(testData);

        auto promise = std::async(std::launch::async, &BranchBound<T>::branchBoundAlgorithm, &branchBound);

        std::chrono::seconds span(maxTimeSeconds);
        if (promise.wait_for(span) == std::future_status::timeout) {
            std::cout << "Algorithm exceeded set time" << std::endl;
            branchBound.isRunning = false;
            failedTries++;
        }
        try {
            auto resultTuple = promise.get();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::get<2>(resultTuple)).count();
            std::cout << "Algorithm finished in " << duration << " nanoseconds" << std::endl;
            result.push_back(duration);
            success = true;
        } catch (std::runtime_error &e) {
        }


        if (success) {
            N++;
            success = false;
            failedTries = 0;
        } else if (failedTries >= 1) {
            result.insert(result.begin(), N - 1);
            if (type == "DFS")
                fileOperator::saveResultFile("BBDFSMaxN.csv", result);
            else if (type == "BestFirst")
                fileOperator::saveResultFile("BBBestFirstMaxN.csv", result);
            return;
        }
    }
}

template void tester::maxProblemSizeBranchBound<std::stack<Node>>(const int& maxTimeSeconds, const std::string &type);

template void tester::maxProblemSizeBranchBound<nodePriorityQueue>(const int& maxTimeSeconds, const std::string &type);

