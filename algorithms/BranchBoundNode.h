//
// Created by Michał Zychowicz on 12/11/2023.
//

#ifndef PEA_ZAD1_BRANCHBOUNDNODE_H
#define PEA_ZAD1_BRANCHBOUNDNODE_H

#include <vector>

// node struct
struct Node {
    int lowerBound;
    std::vector<int> path;
};

#endif //PEA_ZAD1_BRANCHBOUNDNODE_H
