
#include "NetBuilder.h"
#include "utils.h"
#include "Point3D.h"
#include "Net.h"
#include "NavGraph.h"
#include "config.h"
#include "Draw.h"

NetBuilder::NetBuilder() {
  net = new Net();
}



PointCoords3D GetBlockCoords(PointIds3D xyz_id) {
  PointCoords3D res(3);
  for (int i = 0; i < 3; i++) {
    res[i] = xyz_id[i] * (NEURON_RADIUS + NEURON_SPACING) * 7.f;
  }
  return res;
}

void NetBuilder::AddBlock(PointIds3D xyz_id, int radius) {
  blocks.push_back(Block { xyz_id, radius });
}

void NetBuilder::AddPathway(PointIds3D from, PointIds3D to, int radius) {
  // 1. Get the radius of the PointIds3D. 
  // 2. Get the 
}

void NetBuilder::DrawBlock(PointIds3D xyz_id, int radius) {
   if (n == nav_graph->GetCurrentNode()) {
      DrawBox(n->xyz_id, n->r, {0.0f, 1.0f, 0.0f, 0.2f});
    }
    else {
      DrawBox(n->xyz_id, n->r, {0.0f, 0.0f, 1.0f, 0.1f});
    }
}

void NetBuilder::DrawPathway(PointIds3D from, PointIds3D to, int radius) {

}

void NetBuilder::AddRectangle(PointIds3D start, PointIds3D dxyz, PointIds3D step, std::size_t n) {
  std::vector<PointIds3D> start_points = GetCoordsInRectangularPrism(start, dxyz);
  std::vector<std::vector<PointIds3D>> layers(0);

  // Get coordinates of all the layers. 
  for (std::size_t i = 0; i < n; i++) {
    std::vector<PointIds3D> layer(0);
    for (auto point : start_points) {
      layer.push_back({point[0] + (int)i * step[0], point[1] + (int)i * step[1], point[2] + (int)i * step[2]});
    }
    layers.push_back(layer);
  }

  for (auto layer : layers) {
    for (auto point : layer) {
      net->EnableNeuron(point);
    }
  }

  // Add synapses (neurons added implicitly).
  for (std::size_t i = 0; i < layers.size() - 1; i++) {
    for (std::size_t j = 0; j < layers[i].size(); j++) {
      for (std::size_t k = 0; k < layers[i + 1].size(); k++) {
        net->EnableSynapse(layers[i][j], layers[i + 1][k]);
      }
    }
  }
}

void NetBuilder::AddMap(PointIds3D start, PointIds3D dxyzs, PointIds3D end, PointIds3D dxyze) {
  std::vector<PointIds3D> start_points = GetCoordsInRectangularPrism(start, dxyzs);
  std::vector<PointIds3D> end_points = GetCoordsInRectangularPrism(end, dxyze);

  for (auto start_point : start_points) {
    for (auto end_point : end_points) {
      net->EnableNeuron(start_point);
      net->EnableNeuron(end_point);
      net->EnableSynapse(start_point, end_point);
    }
  }
}

void NetBuilder::AddMapByCenter(PointIds3D start_center, PointIds3D start_rxyz, PointIds3D end_center, PointIds3D end_rxyz) {
  std::vector<PointIds3D> start_points(0);
  for (int x = start_center[0] - start_rxyz[0]; x < start_center[0] + start_rxyz[0]; x++) {
    for (int y = start_center[1] - start_rxyz[1]; y < start_center[1] + start_rxyz[1]; y++) {
      for (int z = start_center[2] - start_rxyz[2]; z < start_center[2] + start_rxyz[2]; z++) {
        start_points.push_back({x, y, z});
      }
    }
  }
  std::vector<PointIds3D> end_points(0);
  for (int x = end_center[0] - end_rxyz[0]; x < end_center[0] + end_rxyz[0]; x++) {
    for (int y = end_center[1] - end_rxyz[1]; y < end_center[1] + end_rxyz[1]; y++) {
      for (int z = end_center[2] - end_rxyz[2]; z < end_center[2] + end_rxyz[2]; z++) {
        end_points.push_back({x, y, z});
      }
    }
  }
  for (auto start_point : start_points) {
    for (auto end_point : end_points) {
      net->EnableNeuron(start_point);
      net->EnableNeuron(end_point);
      net->EnableSynapse(start_point, end_point);
    }
  }
}

std::vector<Neuron*> NetBuilder::GetNeuronsInRadius(PointIds3D center, int r) {
  std::vector<Neuron*> res(0);
  for (int x = center[0] - r; x < center[0] + r; x++) {
    for (int y = center[1] - r; y < center[1] + r; y++) {
      for (int z = center[2] - r; z < center[2] + r; z++) {
        res.push_back(net->GetNeuron({x, y, z}));
      }
    }
  }
  return res;
}

std::vector<Synapse*> NetBuilder::GetSynapsesInRadius(PointIds3D center, int r) {
  std::vector<Synapse*> res(0);
  for (Neuron* neuron : GetNeuronsInRadius(center, r)) {
    for (Synapse* synapse : neuron->synapses) {
      res.push_back(synapse);
    }
  }
  return res;
}

float NetBuilder::NFiresPerSecond(PointIds3D center, int r) {
  float res = 0.f;
  for (Neuron* neuron : GetNeuronsInRadius(center, r)) {
    res += neuron->NFires();
  }
  return res / N_TICKS_TO_TRACK;
}

float NetBuilder::TotalEnergy(PointIds3D center, int r) {
  float res = 0.f;
  for (Neuron* neuron : GetNeuronsInRadius(center, r)) {
    res += neuron->energy;
  }
  return res;
}

float NetBuilder::AverageTolerance(PointIds3D center, int r) {
  float res = 0.f;
  for (Neuron* neuron : GetNeuronsInRadius(center, r)) {
    res += neuron->GetTolFactor();
  }
  return res / (float)GetNeuronsInRadius(center, r).size();
}

float NetBuilder::SynapticVariance(PointIds3D center, int r) {
  float res = 0.f;
  std::vector<float> weights(0);
  for (Synapse* synapse : GetSynapsesInRadius(center, r)) {
    weights.push_back(synapse->GetWeight());
  }

  float sum = 0.f;
  for (float weight : weights) {
    sum += weight;
  }
  float mean = sum / (float)weights.size();

  for (float weight : weights) {
    res += (weight - mean) * (weight - mean);
  }
  return res / (float)weights.size();
}