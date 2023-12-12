
#ifndef _INIT_NET_H
#define _INIT_NET_H

#include "utils.h"
#include <vector>
#include "ctest.h" 
#include <iostream>
#include "Block.h"
#include "Neuron.h"
#include "Net.h"
#include "NetBuilder.h"

using namespace std;

NetBuilder net_builder;
Net* net;

void InitNet() {
  net_builder.AddRectangle({0, 0, 0}, {4, 4, 4}, {1, 1, 1}, 3);
  net_builder.net->neuron_id_map[{0, 0, 0}]->energy = 1.01f;
  Synapse* synapse = net_builder.net->neuron_id_map[{1, 1, 1}]->synapses[0];
  synapse->SetWeight(1.01f);
  net = net_builder.net;

  // net_builder.net.Print();

  // for (int l = 0; l < 3; l++) {
  //   net_builder.net.Tick();
  //   net_builder.net.Print();
  // }

  // std::cout << "GetTolFactor(0): " << GetTolFactor(0) << std::endl;
}

typedef float Proportion;
void DrawNeuron(vector<int> xyz, vector<Proportion> rgba);
void DrawSynapse(vector<int> start, vector<int> end, vector<Proportion> rgba);

void DrawNeuronFiring(vector<int> xyz) {
  DrawNeuron(xyz, { 0.f, 1.0f, 1.0f, 0.7f });
}

void DrawNeuronResting(vector<int> xyz) {
  DrawNeuron(xyz, { 0.5f, 0.5f, 0.5f, 0.3f });
}

void DrawNet() {
  for (auto kv : net->neuron_id_map) {
    Neuron* n = kv.second;
    vector<int> xyz = kv.first;
    if (n->JustFired()) {
      DrawNeuronFiring(xyz);
    }
    else {
      DrawNeuronResting(xyz);
    }
  }

  // TODO: Adding drawing synapses firing or not. 
  // The following is only for drawing synapses in the first place, not if they're firing or not. 
  for (auto kv : net->neuron_id_map) {
    Neuron* n = kv.second;
    vector<int> xyz = kv.first;
    for (Synapse* s : n->synapses) {
      DrawSynapse(s->from.xyz, n->xyz, {0.5f, 0.5f, 0.5f, 0.2f});
    }
  }
}

#endif