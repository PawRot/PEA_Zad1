#ifndef PEA_ZAD1_BRUTEFORCE_H
#define PEA_ZAD1_BRUTEFORCE_H

#include <iostream>
#include <vector>
#include <numeric>



class bruteForce {
public:
    explicit bruteForce(const std::vector<std::vector<int>> &matrix);

    ~bruteForce();

    std::tuple<int, std::vector<int>> bruteForceAlgorithm();

private:
    std::vector<std::vector<int>> matrix;
    int numberOfCities;
    int bestPath;
    std::vector<int> citiesIndexes;
    std::vector<int> bestPathIndexes;

};


#endif //PEA_ZAD1_BRUTEFORCE_H
