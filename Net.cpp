
#include "Net.h"
#include <iostream>

void Net::EnableNeuron(PointIds3D xyz) {
  if (!HasNeuron(xyz)) {
    ForceEnableNeuron(xyz);
  }
}

bool Net::HasNeuron(PointIds3D xyz) {
  return neuron_id_map.find(xyz) != neuron_id_map.end();
}

void Net::ForceEnableNeuron(PointIds3D xyz) {
  Neuron* n = new Neuron();
  n->xyz = xyz;
  neuron_id_map[xyz] = n;
}

void Net::EnableSynapse(PointIds3D from, PointIds3D to) {
  EnableNeuron(from);
  EnableNeuron(to);
  Neuron* sender = neuron_id_map[from];
  Neuron* receiver = neuron_id_map[to];
  Synapse* synapse = new Synapse(*sender, *receiver);
  receiver->AddSynapse(synapse);
  sender->AddOutgoingSynapse(synapse);
}

void Net::Tick() {
  for (auto kv : neuron_id_map) {
    kv.second->SetFiredFlag();
  }
}

Net::Net() {}

void Net::Print() {
  std::cout << "Net =====" << std::endl;
  std::cout << "Neurons: " << std::endl;
  for (auto kv : neuron_id_map) {
    std::cout << kv.first[0] << " " << kv.first[1] << " " << kv.first[2] << " " << kv.second->energy << std::endl;
  }
  std::cout << "Synapses: " << std::endl;
  for (auto kv : neuron_id_map) {
    for (auto synapse : kv.second->synapses) {
      std::cout << synapse->from.xyz[0] << " " << synapse->from.xyz[1] << " " << synapse->from.xyz[2] << "=>" << synapse->to.xyz[0] << " " << synapse->to.xyz[1] << " " << synapse->to.xyz[2] << " w: " << synapse->GetWeight() << std::endl;
    }
  }
  std::cout << "=========" << std::endl;
}
