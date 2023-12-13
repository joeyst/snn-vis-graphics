
#include "Net.h"
#include "Point3D.h"
#include "Direction.h"
#include <vector>

#ifndef _NET_BUILDER_H
#define _NET_BUILDER_H

class NavGraph;
class NetBuilder {
  /*
  AddRectangle: 
    start => starting point. 
    dxyz  => (N, M, 0) | (N, 0, M) | (0, N, M). Creates initial plane. N and M can be negative. 
    step  => jump rate in each dimension. 
    n     => number of layers. 
  */
  public:
    Net *net;
    void AddRectangle(PointIds3D start, PointIds3D dxyz, PointIds3D step, std::size_t n);
    NetBuilder();
    void AddMap(PointIds3D start, PointIds3D dxyzs, PointIds3D end, PointIds3D dxyze);
    std::vector<Neuron*> GetNeuronsInRadius(PointIds3D center, int r);
    std::vector<Synapse*> GetSynapsesInRadius(PointIds3D center, int r);
    float NFiresPerSecond(PointIds3D center, int r);
    float TotalEnergy(PointIds3D center, int r);
    float AverageTolerance(PointIds3D center, int r);
    float SynapticVariance(PointIds3D center, int r);
    float AverageSynapseWeight(PointIds3D center, int r);
    float AverageSynapseChange(PointIds3D center, int r);
};

#endif 
