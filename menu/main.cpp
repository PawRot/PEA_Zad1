#include <iostream>

void showMenuOptions();

void loadFromFile();

void generateData();

void displayCurrentData();

void startBruteForce();



int main() {
    // punkt wejścia do programu
    int choice = 0;
    bool dataLoaded = false;

    do {
        std::cin.clear();

        showMenuOptions();
        std::cin >> choice;

        switch (choice) {
            case 1:
                loadFromFile();
                break;
            case 2:
                generateData();
                break;
            case 3:
//                displayCurrentData();
                break;
            case 4:
//                startBruteForce();
                break;
            default:
                break;
        }
    }while (choice != 0);
}

void showMenuOptions() {
    std::cout << "1. Load test data from file" << std::endl;
    std::cout << "2. Generate test data" << std::endl;
    std::cout << "3. Display current test data" << std::endl;
    std::cout << "4. Start Brute Force algorithm" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void loadFromFile(){
    std::cout << "Enter file name: ";
    std::string fileName;
    std::cin >> fileName;

    std::cout << "Loading data from file: " << fileName << std::endl;
}

void generateData(){
    std::cout << "Enter number of cities: ";
    int numberOfCities;
    std::cin >> numberOfCities;

    std::cout << "Enter maximum distance between cities: ";
    int maximumDistance;
    std::cin >> maximumDistance;

    std::cout << "Generating test data" << std::endl;
}