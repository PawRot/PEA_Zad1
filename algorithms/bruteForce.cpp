#include "bruteForce.h"

using std::vector;

bruteForce::bruteForce(const vector<vector<int>> &matrix) {
    this->matrix = matrix;
    numberOfCities = static_cast<int>(matrix.size());
    bestPath = INT_MAX;
    isRunning = true;
    citiesIndexes = vector<int>(numberOfCities);
    bestPathIndexes = vector<int>(numberOfCities);
    std::iota(citiesIndexes.begin(), citiesIndexes.end(), 0);
}

bruteForce::~bruteForce() = default;


std::tuple<int, vector<int>, std::chrono::duration<float>>
bruteForce::bruteForceAlgorithm() {
    // Start the timer to measure the execution time of the algorithm
    auto start = std::chrono::steady_clock::now();

    // Loop over all permutations of the cities
    do {
        int currentPath = 0;

        // Calculate the path length for the current permutation of cities
        for (int i = 0; i < numberOfCities - 1; i++) {
            currentPath += matrix[citiesIndexes[i]][citiesIndexes[i + 1]];
            // If the current path length is already greater than the best path found so far, break the loop
            if (currentPath > bestPath) {
                break;
            }
        }

        // Add the distance from the last city back to the first city to complete the cycle
        currentPath += matrix[citiesIndexes[numberOfCities - 1]][citiesIndexes[0]];

        // If the current path length is less than the best path found so far, update the best path
        if (currentPath < bestPath) {
            bestPath = currentPath;
            bestPathIndexes = citiesIndexes;
            bestPathIndexes.push_back(0);
        }
#ifdef testEnable // if testEnable is defined, this code will be compiled
        if (!isRunning) {
            throw std::runtime_error("Algorithm stopped");
        }
#endif
        // Generate the next permutation of cities
    } while (std::next_permutation(citiesIndexes.begin()+1, citiesIndexes.end()));
    // Funkcja next_permutation używana jest do uzyskiwania kolejnych permutacji, kiedy wszystkie permutacje zostały wygenerowane, zwraca false, co kończy pętle.
    // Możliwa optymalizacja: Ponieważ do każdego miasta musimy wjechać i z niego wyjechać, możemy założyć, że miasto, które jest sprawdzane jako pierwsze (w tym przypadku miasto o indeksie 0),
    // jest zawsze na początku i końcu najlepszej ścieżki (nie musielibyśmy uwzględniać go w permutacjach)

    // Stop the timer and calculate the execution time of the algorithm
    auto end = std::chrono::steady_clock::now();

    auto executionTime = end - start;

    // Return the best path length, the best path, and the execution time of the algorithm
    return {bestPath, bestPathIndexes, executionTime};
}

