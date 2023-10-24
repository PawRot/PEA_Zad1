//
// Created by Michał Zychowicz on 24/10/2023.
//

#include "fileOperator.h"

using std::cout, std::endl;

fileOperator::fileOperator() = default;

fileOperator::~fileOperator() = default;

void fileOperator::saveFile(const string &path, const vector<long long int> &data) {
}

vector<vector<int>> fileOperator::loadDataFromFile(const string &path) {
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
