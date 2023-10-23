//
// Created by Michał Zychowicz on 24/10/2023.
//

#ifndef PEA_ZAD1_FILEOPERATOR_H
#define PEA_ZAD1_FILEOPERATOR_H

#include <iostream>
#include <vector>
#include <fstream>

using std::string, std::vector;


class fileOperator {
public:
    std::fstream file;

    fileOperator();

    ~fileOperator();

    void saveFile(const string &path, const vector<long long int> &data);

    vector<vector<int>> loadDataFromFile(const string &path);
};


#endif //PEA_ZAD1_FILEOPERATOR_H
