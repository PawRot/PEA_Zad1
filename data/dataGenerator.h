//
// Created by Michał Zychowicz on 24/10/2023.
//

#ifndef PEA_ZAD1_DATAGENERATOR_H
#define PEA_ZAD1_DATAGENERATOR_H

#include <vector>
#include <random>

using std::vector;


class dataGenerator {
public:
    dataGenerator();

    ~dataGenerator();

    static vector<vector<int>> generateTestData(int numberOfCities, int maxDistance);

};


#endif //PEA_ZAD1_DATAGENERATOR_H
