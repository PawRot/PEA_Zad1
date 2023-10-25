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
    fileOperator();

    ~fileOperator();
    static void saveDataFile(const string &path, const vector<vector<int>> &data);
    [[deprecated("Function not yet implemented")]]
    static void saveResultFile(const string &path);

    static vector<vector<int>> loadDataFromFile(const string &path);
};


#endif //PEA_ZAD1_FILEOPERATOR_H
