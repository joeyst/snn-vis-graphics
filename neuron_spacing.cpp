
#include "neuron_spacing.h" 
#include "utils.h"
#include "config.h"
#include "Point3D.h"

PointCoords3D GetNeuronCoords(PointIds3D xyz) {
  PointCoords3D coords;
  for (std::size_t i = 0; i < xyz.size(); i++) {
    coords.push_back(xyz[i] * NEURON_TOTAL_DIST);
  }
  return coords;
}

std::pair<PointCoords3D, PointCoords3D> GetSynapseEndpoints(const PointIds3D& start, const PointIds3D& end) {
  PointCoords3D startCoords = GetNeuronCoords(start);
  PointCoords3D endCoords = GetNeuronCoords(end);
  return GetConnectionEndpoints(startCoords, endCoords, SYNAPSE_FILL_PROP);
}
