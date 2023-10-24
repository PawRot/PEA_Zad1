//
// Created by Michał Zychowicz on 24/10/2023.
//

#include "dataGenerator.h"


vector<vector<int>> dataGenerator::generateTestData(int numberOfCities, int maxDistance) {
    vector<vector<int>> tab(numberOfCities, vector<int>(numberOfCities));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, maxDistance);

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
