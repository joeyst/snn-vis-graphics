
#include "Point3D.h"
#include "NavNode.h"
#include "config.h"
#include "utils.h"
#include "Neuron.h"

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

NavNode::NavNode(PointIds3D xyz_id, int r) : xyz_id(xyz_id), r(r) {
  std::vector<PointIds3D> point_ids = GetPointIdsInRadius(xyz_id, r);
  for (auto point_id : point_ids) {
    neurons.push_back(new Neuron(point_id));
  }
}

std::vector<PointIds3D> NavNode::PointIds() {
  return ::GetPointIdsInRadius(xyz_id, r);
}

void NavNode::Stimulate() {
  for (auto neuron : neurons) {
    if (RandomWeight() < 0.3f) {
      neuron->energy += NEURON_FIRE_THRESH;
    }
  }
}

void NavNode::Inhibit() {
  for (auto neuron : neurons) {
    neuron->energy -= NEURON_FIRE_THRESH;
  }
}
