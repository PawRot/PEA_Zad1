#ifndef PEA_ZAD1_DATAGENERATOR_H
#define PEA_ZAD1_DATAGENERATOR_H

#include <vector>
#include <random>


class dataGenerator {
public:
    static std::vector<std::vector<int>>
    generateTestData(unsigned int numberOfCities, unsigned int maxDistance, unsigned int minimumDistance);

};


#endif //PEA_ZAD1_DATAGENERATOR_H
