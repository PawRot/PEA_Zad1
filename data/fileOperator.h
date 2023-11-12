#ifndef PEA_ZAD1_FILEOPERATOR_H
#define PEA_ZAD1_FILEOPERATOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>




class fileOperator {
public:
    fileOperator();

    ~fileOperator();
    static void saveDataFile(const std::string &path, const std::vector<std::vector<int>> &data);
    static void saveResultFile(const std::string &path, const std::vector<long long> &data);

    static std::vector<std::vector<int>> loadDataFromFile(const std::string &path);
};


#endif //PEA_ZAD1_FILEOPERATOR_H
