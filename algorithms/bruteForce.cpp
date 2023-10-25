//
// Created by Michał Zychowicz on 24/10/2023.
//

#include "bruteForce.h"

bruteForce::bruteForce(const vector<vector<int>>& graph) {
    this->graph = graph;
    this->numberOfCities = static_cast<int>(graph.size());
    bestPath = INT_MAX;
    citiesIndexes = vector<int>(numberOfCities);
    bestPathIndexes = vector<int>(numberOfCities);
    std::iota(citiesIndexes.begin(), citiesIndexes.end(), 0);
}

void bruteForce::bruteForceAlgorithm() { // TODO ogarnąć jak działą ten algorytm XD (zastanowić się dlaczego zawsze najkrótsza ścieżka jest z miasta 0)
    do {
        int currentPath = 0;
        for (int i = 0; i < numberOfCities - 1; i++) {
            currentPath += graph[citiesIndexes[i]][citiesIndexes[i + 1]];
        }
        currentPath += graph[citiesIndexes[numberOfCities - 1]][citiesIndexes[0]];
//        std::cout << citiesIndexes[0] << std::endl;

        if (currentPath < bestPath) {
            bestPath = currentPath;
            bestPathIndexes = citiesIndexes;
            bestPathIndexes.push_back(0);
//            std::cout << "Best path: " << bestPath << std::endl;
//            for (int i = 0; i < numberOfCities; i++) {
//                std::cout << bestPathIndexes[i] << " ";
//            }
//            std::cout << bestPathIndexes[0] << std::endl;
        }
    } while (std::next_permutation(citiesIndexes.begin(), citiesIndexes.end()));

    std::cout << "Best path: " << bestPath << std::endl;
    std::cout << "Path: ";
    for (int i = 0; i < numberOfCities+1; i++) {
        std::cout << bestPathIndexes[i] << " ";
    }
//    std::cout << bestPathIndexes[0] << std::endl;

}

bruteForce::~bruteForce() = default;
