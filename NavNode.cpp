
#include "Point3D.h"
#include "NavNode.h"

std::vector<PointIds3D> GetPointIdsInRadius(PointIds3D center, int r) {
  std::vector<PointIds3D> res(0);
  for (int x = center[0] - r; x < center[0] + r; x++) {
    for (int y = center[1] - r; y < center[1] + r; y++) {
      for (int z = center[2] - r; z < center[2] + r; z++) {
        res.push_back({x, y, z});
      }
    }
  }
  return res;
}

std::vector<PointIds3D> NavNode::PointIds() {
  return ::GetPointIdsInRadius(xyz_id, r);
}
