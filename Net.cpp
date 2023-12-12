
#include "Net.h"
#include <iostream>
#include "utils.h"

float Net::GetModeValue() {
  if (init_mode == INIT_MODE_RANDOM) {
    return RandomWeight();
  }
  else if (init_mode == INIT_MODE_ZERO) {
    return 0.f;
  }
  else if (init_mode == INIT_MODE_ONE) {
    return 1.f;
  }
  else {
    std::cout << "Error: invalid init_mode: " << init_mode << std::endl;
    exit(1);
  }
}

void Net::EnableNeuron(PointIds3D xyz) {
  if (!HasNeuron(xyz)) {
    ForceEnableNeuron(xyz);
    Neuron* n = GetNeuron(xyz);
    n->energy = GetModeValue();
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

std::vector<Neuron*> Net::GetNeurons() {
  std::vector<Neuron*> neurons(0);
  for (auto kv : neuron_id_map) {
    neurons.push_back(kv.second);
  }
  return neurons;
}

std::vector<Synapse*> Net::GetSynapses() {
  std::vector<Synapse*> synapses(0);
  for (auto kv : neuron_id_map) {
    for (Synapse* synapse : kv.second->synapses) {
      synapses.push_back(synapse);
    }
  }
  return synapses;
}

void Net::EnableSynapse(PointIds3D from, PointIds3D to) {
  EnableNeuron(from);
  EnableNeuron(to);
  Neuron* sender = neuron_id_map[from];
  Neuron* receiver = neuron_id_map[to];
  Synapse* synapse = new Synapse(*sender, *receiver);
  synapse->OverwriteWeight(GetModeValue());
  receiver->AddSynapse(synapse);
  sender->AddOutgoingSynapse(synapse);
}

void Net::Tick() {
  for (auto kv : neuron_id_map) {
    kv.second->SetFiredFlag();
  }
  for (auto kv : neuron_id_map) {
    kv.second->ZeroOrDecayEnergy();
  }
  for (auto kv : neuron_id_map) {
    kv.second->AddAssignIncomingEnergy();
  }
  for (auto kv : neuron_id_map) {
    kv.second->ApplyOjas();
  }
  for (auto kv : neuron_id_map) {
    kv.second->PushFiringToBuffer();
  }
}

Net::Net() : init_number(0.3f), init_mode(INIT_MODE_RANDOM) {}

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

Neuron* Net::GetNeuron(PointIds3D xyz) {
  return neuron_id_map[xyz];
}

std::vector<Synapse*> Net::GetSynapses(PointIds3D from, PointIds3D to) {
  return GetNeuron(to)->GetSynapsesByIndex(from);
}
