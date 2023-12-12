
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
  net_builder.AddRectangle({0, 0, 0}, {2, 2, 2}, {2, 2, 2}, 3);
  net_builder.net->neuron_id_map[{0, 0, 0}]->energy = 1.01f;
  Synapse* synapse = net_builder.net->neuron_id_map[{2, 2, 2}]->synapses[0];
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
  DrawNeuron(xyz, { 1.0f, 1.0f, 0.0f, 0.7f });
}

void DrawNeuronResting(vector<int> xyz) {
  DrawNeuron(xyz, { 0.5f, 0.5f, 0.5f, 0.3f });
}

void DrawNet() {
  for (auto kv : net->neuron_id_map) {
    Neuron* n = kv.second;
    vector<int> xyz = kv.first;
    if (n->EnergyIsAboveThreshold()) {
      DrawNeuronFiring(xyz);
    }
    else {
      DrawNeuronResting(xyz);
    }
  }

  // The following is only for drawing synapses in the first place, not if they're firing or not. 
  for (auto kv : net->neuron_id_map) {
    Neuron* n = kv.second;
    vector<int> xyz = kv.first;
    for (Synapse* s : n->synapses) {
      if (s->from.EnergyIsAboveThreshold()) {
        DrawSynapse(s->from.xyz, n->xyz, {1.0f, 1.0f, 0.0f, 0.2f});
      }
      else {
        DrawSynapse(s->from.xyz, n->xyz, {0.5f, 0.5f, 0.5f, 0.05f});
      }
    }
  }
}

#endif
