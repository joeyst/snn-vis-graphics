
#include "tuple_hash.h"
#include <unordered_map>
#include "Neuron.h"
#include <vector>

#ifndef _NET_H
#define _NET_H

enum InitMode {
  INIT_MODE_RANDOM,
  INIT_MODE_ZERO,
  INIT_MODE_ONE,
  INIT_MODE_NUMBER
};

class Net {
  public:
    void EnableNeuron(PointIds3D xyz);
    void EnableSynapse(PointIds3D from, PointIds3D to);
    void Tick();
    Net();
    void Print();
    Neuron* GetNeuron(PointIds3D xyz);
    std::vector<Synapse*> GetSynapses(PointIds3D from, PointIds3D to);
    std::vector<Neuron*> GetNeurons();
    std::vector<Synapse*> GetSynapses();

  private:
    InitMode init_mode;
    std::unordered_map<PointIds3D, Neuron*, container_hash<PointIds3D>> neuron_id_map;
    bool HasNeuron(PointIds3D xyz);
    void ForceEnableNeuron(PointIds3D xyz);
    float init_number;
    float GetModeValue();
};

#endif
