
#include "NavGraph.h"
#include "NavNode.h"
#include "Point3D.h"

NavGraph::NavGraph() {
  net_builder = new NetBuilder();
  current = {0, 0, 0};
}

/* User interaction. */
void NavGraph::Move(PointIds3D xyz_id) {
  for (int i = 0; i < 3; i++) {
    current[i] += xyz_id[i];
  }
}

void NavGraph::Stimulate() {
  GetCurrentNode()->Stimulate();
}

void NavGraph::Inhibit() {
  GetCurrentNode()->Inhibit();
}


/* Node management. */
NavNode* NavGraph::GetNode(PointIds3D xyz_id_) {
  return nodes[xyz_id_];
}

void NavGraph::AddNode(PointIds3D xyz_id_, int r) {
  NavNode* node = new NavNode(xyz_id_, r);
  nodes[xyz_id_] = node;
  for (Neuron* neuron : node->neurons) {
    net_builder->net->EnableNeuron(neuron->xyz);
  }
}

std::vector<NavNode*> NavGraph::GetNavNodes() {
  std::vector<NavNode*> res(0);
  for (auto node : nodes) {
    res.push_back(node.second);
  }
  return res;
}

/*
void NavGraph::RemoveNode() {
  
  // delete GetCurrentNode();
}
*/

/* Current node management. */
NavNode* NavGraph::GetCurrentNode() {
  return GetNode(current);
}

void NavGraph::AddCurrentNode(int r) {
  AddNode(current, r);
}
