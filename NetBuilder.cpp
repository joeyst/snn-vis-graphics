
#include "NetBuilder.h"
#include "utils.h"
#include "Point3D.h"
#include "Net.h"
#include "NavGraph.h"
#include "config.h"

NetBuilder::NetBuilder() {
  net = new Net();
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
