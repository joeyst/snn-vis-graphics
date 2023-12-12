
#ifndef _NAV_GRAGH_H
#define _NAV_GRAGH_H
#include <unordered_map>
#include "tuple_hash.h"

class NavNode {
  private:
    std::vector<int> xyz_id;
    int r;
    std::vector<NavNode*> next_nodes;
    std::vector<Neuron*> neurons;
};

class NavGraph {
  private:
    std::unordered_map<PointIds3D, NavNode*> nodes;
    NavNode* current_node;
};

#endif
