#include "bruteForce.h"

using std::vector;

bruteForce::bruteForce(const vector<vector<int>> &matrix) {
    this->matrix = matrix;
    numberOfCities = static_cast<int>(matrix.size());
    bestPath = INT_MAX;
    citiesIndexes = vector<int>(numberOfCities);
    bestPathIndexes = vector<int>(numberOfCities);
    std::iota(citiesIndexes.begin(), citiesIndexes.end(), 0);
}

bruteForce::~bruteForce() = default;


std::tuple<int, vector<int>>
bruteForce::bruteForceAlgorithm() {
    do {
        int currentPath = 0;
        for (int i = 0; i < numberOfCities - 1; i++) {
            currentPath += matrix[citiesIndexes[i]][citiesIndexes[i + 1]];
            if (currentPath > bestPath) {
                break;
            }
        }
        currentPath += matrix[citiesIndexes[numberOfCities - 1]][citiesIndexes[0]];

        if (currentPath < bestPath) {
            bestPath = currentPath;
            bestPathIndexes = citiesIndexes;
            bestPathIndexes.push_back(0);
        }
    } while (std::next_permutation(citiesIndexes.begin(), citiesIndexes.end()));
    // Funkcja next_permutation używana jest do uzyskiwania kolejnych permutacji, kiedy wszystkie permutacje zostały wygenerowane, zwraca false, co kończy pętle.
    // Możliwa optymalizacja: Ponieważ do każdego miasta musimy wjechać i z niego wyjechać, możemy założyć, że miasto, które jest sprawdzane jako pierwsze (w tym przypadku miasto o indeksie 0),
    // jest zawsze na początku i końcu najlepszej ścieżki (nie musielibyśmy uwzględniać go w permutacjach)

    return {bestPath, bestPathIndexes};
}

