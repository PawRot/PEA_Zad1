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
    static vector<vector<int>> generateTestData(unsigned int numberOfCities, unsigned int maxDistance, unsigned int minimumDistance);

};


#endif //PEA_ZAD1_DATAGENERATOR_H
