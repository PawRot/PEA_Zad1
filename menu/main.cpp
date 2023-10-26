#include <iostream>
#include <thread>
#include <future>
#include "../data/fileOperator.h"
#include "../data/dataGenerator.h"
#include "../algorithms/bruteForce.h"

using std::vector, std::string;

void showMenuOptions();

vector<vector<int>> loadFromFile(bool &dataLoaded);

vector<vector<int>> generateData(bool &dataLoaded);

void displayCurrentData(vector<vector<int>> &data);

void startBruteForce(vector<vector<int>> &testData);

int main() {
    // punkt wejścia do programu
    int choice = -1;
    string input;
    bool dataLoaded = false;
    vector<vector<int>> testData;

    do {

        showMenuOptions();
        std::cin >> input;

        // wybór opcji menu
        try {
            choice = std::stoi(input);
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid argument" << std::endl << std::endl;
            choice = -1;
        }


        switch (choice) {
            case 1:
                std::cout << std::endl;
                testData = loadFromFile(dataLoaded);
                std::cout << std::endl;
                break;
            case 2:
                std::cout << std::endl;
                testData = generateData(dataLoaded);
                std::cout << std::endl;
                break;
            case 3:
                std::cout << std::endl;
                if (dataLoaded) {
                    displayCurrentData(testData);
                } else {
                    std::cout << "No data loaded" << std::endl;
                }
                std::cout << std::endl;
                break;
            case 4:
                std::cout << std::endl;
                if (dataLoaded) {
                    startBruteForce(testData);
                } else {
                    std::cout << "No data loaded" << std::endl;
                }
                std::cout << std::endl;
                break;
            case 9:
                std::cout << std::endl;
                if(dataLoaded) {
                    std::cout << "Provide file name or whole path" << std::endl;
                    string path;
                    std::cin >> path;
                    fileOperator::saveDataFile(path, testData);
                    std::cout << std::endl;
                } else {
                    std::cout << "No data loaded" << std::endl;
                }
            default:
                break;
        }
    } while (choice != 0);
}

void showMenuOptions() {
    std::cout << "1. Load test data from file" << std::endl;
    std::cout << "2. Generate test data" << std::endl;
    std::cout << "3. Display current test data" << std::endl;
    std::cout << "4. Start Brute Force algorithm" << std::endl;
    std::cout << "9. Save current data to file" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

vector<vector<int>> loadFromFile(bool &dataLoaded) {
    std::cout << "Enter file path: ";
    string filePath;
    std::cin >> filePath;

    std::cout << "Loading data from file: " << filePath << std::endl;
    auto data = fileOperator::loadDataFromFile(filePath);
    if (!data.empty()) {
        std::cout << "Data loaded successfully" << std::endl;
        dataLoaded = true;
        return data;
    } else {
        std::cout << "Data not loaded" << std::endl;
        dataLoaded = false;
        return {};
    }

}

vector<vector<int>> generateData(bool &dataLoaded) {
    std::cout << "Enter number of cities: ";
    string input;
    std::cin >> input;
    unsigned int numberOfCities;
    try {
        numberOfCities = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        dataLoaded = false;
        return {};
    }

    std::cout << "Enter minimum distance between cities: ";
    unsigned int minimumDistance;
    std::cin >> input;

    try {
        minimumDistance = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        dataLoaded = false;
        return {};
    }

    std::cout << "Enter maximum distance between cities: ";
    unsigned int maximumDistance;
    std::cin >> input;

    try {
        maximumDistance = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        dataLoaded = false;
        return {};
    }
    std::cout << "Generating test data" << std::endl;
    auto data = dataGenerator::generateTestData(numberOfCities, maximumDistance, minimumDistance);
    if (!data.empty()) {
        std::cout << "Data generated successfully" << std::endl;
        dataLoaded = true;
        return data;
    } else {
        std::cout << "Data not generated" << std::endl;
        dataLoaded = false;
        return {};
    }

}

void displayCurrentData(vector<vector<int>> &data) {
    int numberOfCities = static_cast<int>(data.size());
    std::cout << "Current number of cities: " << numberOfCities << std::endl;
    std::cout << "Current test data matrix: " << std::endl;
    for (int i = 0; i < numberOfCities; ++i) {
        for (int j = 0; j < numberOfCities; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void startBruteForce(vector<vector<int>> &testData) {
    std::cout << "Starting Brute Force algorithm" << std::endl;
    bruteForce bruteForce(testData);
    auto start = std::chrono::steady_clock::now();

//    auto resultTuple = bruteForce.bruteForceAlgorithm(); //synchroniczne wykonanie


    std::future<std::tuple<int, std::vector<int>>> promise = std::async(&bruteForce::bruteForceAlgorithm, &bruteForce);
//    std::cout << "Example of asynchronous execution" << std::endl;
//    ten kod sprawdza, czy algorytm się skończył, jeśli nie to co sekundę wypisuje komunikat
    std::future_status status;
    do {
        status = promise.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::ready) {
            std::cout << "Algorithm is done running" << std::endl;
        }
    } while (status != std::future_status::ready);

    auto resultTuple = promise.get();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Algorithm finished" << std::endl;
    std::cout << "Result: " << std::endl;
    std::cout << "Path length: " << std::get<0>(resultTuple) << std::endl;
    std::cout << "Path: ";
    for (int i = 0; i < static_cast<int>(testData.size())+1; i++) {
        std::cout << std::get<1>(resultTuple)[i];
        if (i < static_cast<int>(testData.size())) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "Execution time was: " << duration << " miliseconds" << std::endl;
}