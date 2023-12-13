
#ifndef _NAV_GRAGH_H
#define _NAV_GRAGH_H
#include <unordered_map>
#include "tuple_hash.h"
#include "Point3D.h"
#include <unordered_set>
#include "NavNode.h"

class NavGraph {
  /*
  Stores current location in grid of blocks. 
  Provides interface for stimulating or inhibiting the current block. 
  */
  void AddNode(int r);
  void RemoveNode();
  void Move(PointIds3D dxyz_id);
  void Stimulate();
  void Inhibit();

  NavNode* GetCurrentNode();
  NavNode* GetNode(PointIds3D xyz_id);

  private:
    std::unordered_map<PointIds3D, NavNode*, container_hash<PointIds3D>> nodes;
    PointIds3D current;
};

#endif
