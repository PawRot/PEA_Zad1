#ifndef PEA_ZAD1_BRUTEFORCE_H
#define PEA_ZAD1_BRUTEFORCE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <atomic>
#include <chrono>


class bruteForce {
public:
    explicit bruteForce(const std::vector<std::vector<int>> &matrix);

    ~bruteForce();

    std::tuple<int, std::vector<int>, std::chrono::duration<float>> bruteForceAlgorithm();

    std::atomic_bool isRunning;

private:
    std::vector<std::vector<int>> matrix;
    int numberOfCities;
    int bestPath;
    std::vector<int> citiesIndexes;
    std::vector<int> bestPathIndexes;

};


#endif //PEA_ZAD1_BRUTEFORCE_H
