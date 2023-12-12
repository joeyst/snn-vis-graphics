
#include "NavGraph.h"
#include "Point3D.h"

std::vector<PointIds3D> GetPointIdsInRadius(PointIds3D center, int r) {
  std::vector<PointIds3D> res(0);
  for (int x = center[0] - r; x < center[0] + r; x++) {
    for (int y = center[1] - r; y < center[1] + r; y++) {
      for (int z = center[2] - r; z < center[2] + r; z++) {
        res.push_back({x, y, z});
      }
    }
  }
}

PointIds3D NavNode::DXYZ(PointIds3D xyz_id_) {
  PointIds3D dxyz_id(0);
  for (int i = 0; i < 3; i++) {
    dxyz_id[i] = xyz_id_[i] - xyz_id[i];
  } 
  return dxyz_id;
}

PointIds3D NavNode::AbsDXYZ(PointIds3D xyz_id_) {
  PointIds3D dxyz_id = DXYZ(xyz_id_);
  PointIds3D abs_dxyz_id(3);
  for (int i = 0; i < 3; i++) {
    abs_dxyz_id[i] = abs(dxyz_id[i]);
  }
  return abs_dxyz_id;
}

bool NavNode::Overlaps(PointIds3D xyz_id_) {
  return MaxRadius(xyz_id_) < 0;
}

int NavNode::MaxRadius(PointIds3D xyz_id_) {
  PointIds3D abs_dxyz_id = AbsDXYZ(xyz_id_);
  return std::max(abs_dxyz_id[0] - 1, std::max(abs_dxyz_id[1] - 1, abs_dxyz_id[2] - 1));
}

bool NavGraph::HasNode(PointIds3D xyz_id_) {
  return nodes.find(xyz_id_) != nodes.end();
}

void NavGraph::AddNode(PointIds3D xyz_id_, int r) {
  NavNode* node = new NavNode(xyz_id_, r);
  nodes[xyz_id_] = node;
  for (PointIds3D p : node->PointIds) {
    occupied.insert(p);
  }
}