#include <iostream>
#include "../data/fileOperator.h"
#include "../data/dataGenerator.h"

void showMenuOptions();

vector<vector<int>> loadFromFile(bool &dataLoaded);

vector<vector<int>> generateData(bool &dataLoaded);

void displayCurrentData(vector<vector<int>> &data);

void startBruteForce();


int main() {
    // punkt wejścia do programu
    int choice = 0;
    bool dataLoaded = false;
    vector<vector<int>> testData;

    do {
        std::cin.clear();

        showMenuOptions();
        std::cin >> choice;

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
                if(dataLoaded){
                    displayCurrentData(testData);
                } else {
                    std::cout << "No data loaded" << std::endl;
                }
                std::cout << std::endl;
                break;
            case 4:
//                startBruteForce();
                break;
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
    std::cout << "0. Exit" << std::endl;
}

vector<vector<int>> loadFromFile(bool &dataLoaded) {
    std::cout << "Enter file path: ";
    std::string filePath;
    std::cin >> filePath;

    std::cout << "Loading data from file: " << filePath << std::endl;
    fileOperator fileOperator;
    auto data = fileOperator.loadDataFromFile(filePath);
    if (!data.empty()) {
        std::cout << "Data loaded successfully" << std::endl;
        dataLoaded = true;
        return data;
    } else {
        std::cout << "Data not loaded" << std::endl;
        return {};
    }

}

vector<vector<int>> generateData(bool &dataLoaded) { //TODO: implement
    std::cout << "Enter number of cities: ";
    int numberOfCities;
    std::cin >> numberOfCities;

    std::cout << "Enter maximum distance between cities: ";
    int maximumDistance;
    std::cin >> maximumDistance;

    std::cout << "Generating test data" << std::endl;


    return {};
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