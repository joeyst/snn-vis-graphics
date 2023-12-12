
#include "tuple_hash.h"
#include <unordered_map>
#include "Neuron.h"
#include <vector>

#ifndef _NET_H
#define _NET_H

class Net {
  public:
    std::unordered_map<PointIds3D, Neuron*, container_hash<PointIds3D>> neuron_id_map;
    void EnableNeuron(PointIds3D xyz);
    void EnableSynapse(PointIds3D from, PointIds3D to);
    void Tick();
    Net();
    void Print();

  private:
    bool HasNeuron(PointIds3D xyz);
    void ForceEnableNeuron(PointIds3D xyz);
};

#endif
