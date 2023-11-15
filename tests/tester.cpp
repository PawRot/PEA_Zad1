
#include "tester.h"

tester::tester() = default;

tester::~tester() = default;

void tester::maxProblemSizeBruteForce(const int &maxTimeSeconds) {

    std::vector<long long> result;
    int failedTries = 0;
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
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::get<2>(resultTuple)).count();
            std::cout << "Algorithm finished in " << duration << "nanoseconds" << std::endl;
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
            fileOperator::saveResultFile("bruteForceMaxN.csv", result);
            return;
        }
    }
}

void tester::testBruteForce(const int &N) {

    std::vector<long long> result;
    int tests = 0;

    while (tests < 100) {

        auto testData = dataGenerator::generateTestData(N, 10, 9999);

        bruteForce bruteForce(testData);

        auto resultTuple = bruteForce.bruteForceAlgorithm();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::get<2>(resultTuple)).count();
        std::cout << "Algorithm finished in " << duration << " nanoseconds" << std::endl;
        result.push_back(duration);

        tests++;
    }

    auto const size = static_cast<int>(result.size());
    auto const average = std::reduce(result.begin(), result.end()) / size;
    std::vector<long long> endResult = {N, average};

//    result.insert(result.begin(), N);
//    std::string fileName = "bruteForce" + std::to_string(N) + ".csv";
    std::string fileName = "bruteForceTest.csv";
    fileOperator::saveResultFile(fileName, endResult);

}



template<typename T>
void tester::maxProblemSizeBranchBound(const int &maxTimeSeconds, const std::string &type) {

    std::vector<long long> result;
    int failedTries = 0;
    std::tuple<bool, int> resultTuple;
    int N = 2;

    while (true) {

        auto testData = dataGenerator::generateTestData(N, 9999, 10);

        resultTuple = runBranchBound<T>(testData, maxTimeSeconds, result, failedTries);



        if (std::get<0>(resultTuple)) {
            N++;
//            success = false;
            failedTries = 0;
        } else if (std::get<1>(resultTuple) >= 3) {
            result.insert(result.begin(), N - 1);
            if (type == "DFS")
                fileOperator::saveResultFile("BBDFSMaxN.csv", result);
            else if (type == "BestFirst")
                fileOperator::saveResultFile("BBBestFirstMaxN.csv", result);
            return;
        }
    }
}

template<typename T>
void tester::testBranchBound(const int &N, const int &maxTimeSeconds,  const std::string &type) {

    std::vector<long long> result;
    int failedTries = 0;
    std::tuple<bool, int> resultTuple;
    int tests = 0;

    while(tests < 20) {

        auto testData = dataGenerator::generateTestData(N, 9999, 10);

        runBranchBound<T>(testData, maxTimeSeconds, result, failedTries);

        tests++;

    }

    auto const size = static_cast<int>(result.size());
    std::vector<long long> endResult;
    if (size == 0){
        endResult = {N, failedTries, -1};

    }else {
        auto const average = std::reduce(result.begin(), result.end()) / size;
        endResult = {N, failedTries, average};
    }


    if (type == "DFS") {
        std::string fileName = "BBDFSTest" + std::to_string(N) + ".csv";
        fileOperator::saveResultFile(fileName, endResult);
    } else if (type == "BestFirst") {
        std::string fileName = "BBBestFirstTest " + std::to_string(N) + ".csv";
        fileOperator::saveResultFile(fileName, endResult);
    }

}

template<typename T>
std::tuple<bool, int> tester::runBranchBound(const std::vector<std::vector<int>> &testData, const int &maxTimeSeconds, std::vector<long long> &result, int &failedTries) {
    BranchBound<T> branchBound(testData);

    auto promise = std::async(std::launch::async, &BranchBound<T>::branchBoundAlgorithm, &branchBound);

    std::chrono::seconds span(maxTimeSeconds);
    if (promise.wait_for(span) == std::future_status::timeout) {
        std::cout << "Algorithm exceeded set time" << std::endl;
        branchBound.isRunning = false;
        failedTries++;
        return {false, failedTries};
    }
    try {
        auto resultTuple = promise.get();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::get<2>(resultTuple)).count();
//        if (!failed) {
            std::cout << "Algorithm finished in " << duration << " nanoseconds" << std::endl;
            result.push_back(duration);
            return {true, failedTries};
//        }
//        return {false, failedTries};
    } catch (std::runtime_error &e) {
        std::cout << "Algorithm execution time was too long, terminated" << std::endl;
        return {false, failedTries};
    }
}

template void tester::maxProblemSizeBranchBound<std::stack<Node>>(const int& maxTimeSeconds, const std::string &type);

template void tester::maxProblemSizeBranchBound<nodePriorityQueue>(const int& maxTimeSeconds, const std::string &type);

template void tester::testBranchBound<std::stack<Node>>(const int &N, const int &maxTimeSeconds, const std::string &type);
template void tester::testBranchBound<nodePriorityQueue>(const int &N, const int &maxTimeSeconds,  const std::string &type);

