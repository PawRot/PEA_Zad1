#include "dataGenerator.h"

using std::vector;

vector<vector<int>>
dataGenerator::generateTestData(const unsigned int numberOfCities, const unsigned int maxDistance, const unsigned int minimumDistance) {
    vector tab(numberOfCities, vector<int>(numberOfCities));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(static_cast<int>(minimumDistance), static_cast<int>(maxDistance));

    for (int i = 0; i < numberOfCities; i++) {
        for (int j = 0; j < numberOfCities; j++) {
            if (i == j) {
                tab[i][j] = 0;
            } else {
                tab[i][j] = dist(mt);
            }
        }
    }
    return tab;
}
