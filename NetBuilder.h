
#include "Net.h"
#include "Point3D.h"
#include "Direction.h"
#include <vector>

#ifndef _NET_BUILDER_H
#define _NET_BUILDER_H

class Block {
  public:
    PointIds3D xyz_id;
    int r;
}

PointCoords3D GetBlockCoords(PointIds3D xyz_id);

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
    std::vector<Block> blocks;

    void AddBlock(PointIds3D xyz_id, int radius);
    void AddPathway(PointIds3D from, PointIds3D to, int radius);

    void AddRectangle(PointIds3D start, PointIds3D dxyz, PointIds3D step, std::size_t n);
    NetBuilder();
    void AddMap(PointIds3D start, PointIds3D dxyzs, PointIds3D end, PointIds3D dxyze);
    void AddMapByCenter(PointIds3D start_center, PointIds3D start_rxyz, PointIds3D end_center, PointIds3D end_rxyz);
    std::vector<Neuron*> GetNeuronsInRadius(PointIds3D center, int r);
    std::vector<Synapse*> GetSynapsesInRadius(PointIds3D center, int r);
    float NFiresPerSecond(PointIds3D center, int r);
    float TotalEnergy(PointIds3D center, int r);
    float AverageTolerance(PointIds3D center, int r);
    float SynapticVariance(PointIds3D center, int r);
    float AverageSynapseWeight(PointIds3D center, int r);
    float AverageSynapseChange(PointIds3D center, int r);

    // Drawing functions. 
    void DrawBlock(PointIds3D xyz_id, int radius);
    void DrawPathway(PointIds3D from, PointIds3D to, int radius);
};

#endif 
