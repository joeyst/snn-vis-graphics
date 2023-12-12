
#ifndef _NAV_GRAGH_H
#define _NAV_GRAGH_H
#include <unordered_map>
#include "tuple_hash.h"
#include "Point3D.h"
#include <unordered_set>

std::vector<PointIds3D> GetPointIdsInRadius(PointIds3D center, int r);

class NavNode {
  public:
    bool Overlaps(PointIds3D xyz_id_);

  private:
    std::vector<int> xyz_id;
    int r;
    std::vector<NavNode*> next_nodes;
    std::vector<Neuron*> neurons;
};

class NavGraph {
  void AddNode(PointIds3D xyz_id, int r);
  private:
    bool HasNode(PointIds3D xyz_id);
    std::unordered_map<PointIds3D, NavNode*, container_hash> nodes;
    PointIds3D current;
    std::unordered_set<PointIds3D, container_hash> occupied;
};

#endif
