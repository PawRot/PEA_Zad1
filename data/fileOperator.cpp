#include "fileOperator.h"

using std::cout, std::endl, std::vector, std::string;

fileOperator::fileOperator() = default;

fileOperator::~fileOperator() = default;

void fileOperator::saveDataFile(const string &path, const vector<vector<int>> &data) {
    std::ofstream file;

    file.open(path, std::ios::out);

    if (file.good()) {
        cout << "File created successfully" << std::endl;
    } else {
        cout << "Failed to create file" << std::endl;
        return;
    }

    if(file.is_open()) {
        int size = static_cast<int>(data.size());
        file << size << std::endl;
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                file << data[i][j] << " ";
            }
            file << std::endl;
        }
    }


}

vector<vector<int>> fileOperator::loadDataFromFile(const string &path) {
    std::ifstream file;
    file.open(path, std::ios::in);
    if (file.good()) {
        cout << "File loaded successfully" << endl;
    } else {
        cout << "File not found" << endl;
    }

    int numberOfCities;

    if (file.is_open()) {
        file >> numberOfCities;

        int distance;
        vector<vector<int>> tab(numberOfCities, vector<int>(numberOfCities));

        if (file.fail()) {
            cout << "File error" << endl;
        } else {
            for (int i = 0; i < numberOfCities; i++) {
                for (int j = 0; j < numberOfCities; j++) {
                    file >> distance;

                    if (file.fail()) {
                        cout << "File error" << endl;
                        break;
                    } else {
                        tab[i][j] = distance;
                    }
                }
            }
            file.close();
            return tab;
        }
    } else {
        cout << "File error" << endl;
    }
    file.close();
    return {};
}

void fileOperator::saveResultFile(const string &path) {

}
