//
// Created by Michał Zychowicz on 24/10/2023.
//

#ifndef PEA_ZAD1_BRUTEFORCE_H
#define PEA_ZAD1_BRUTEFORCE_H

#include <iostream>
#include <vector>
#include <numeric>

using std::vector;


class bruteForce {
public:
    explicit bruteForce(const vector<vector<int>>& graph);

    ~bruteForce();

    void bruteForceAlgorithm();

private:
    vector<vector<int>> graph;
    int numberOfCities;
    int bestPath;
    vector<int> citiesIndexes;
    vector<int> bestPathIndexes;

};


#endif //PEA_ZAD1_BRUTEFORCE_H
