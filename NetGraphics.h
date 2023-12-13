
#ifndef _NET_GRAPHICS_H 
#define _NET_GRAPHICS_H 

#include "utils.h"
#include <vector>
#include "ctest.h" 
#include <iostream>
#include "Block.h"
#include "Neuron.h"
#include "Net.h"
#include "NetBuilder.h"
#include "NavGraph.h"

using namespace std;

NetBuilder net_builder;
Net* net;
NavGraph* nav_graph;

void InitNet() {
  net_builder.AddRectangle({0, 0, 0}, {2, 2, 2}, {2, 2, 2}, 4);
  net_builder.net->GetNeuron({0, 0, 0})->energy = 1.01f;
  net_builder.net->GetNeuron({3, 3, 3})->energy = 1.01f;
  Synapse* synapse = net_builder.net->GetNeuron({2, 2, 2})->synapses[0];
  for (Synapse* s : net_builder.net->GetNeuron({3, 3, 3})->synapses) {
    s->SetWeight(1.01f);
  }
  vector<Synapse*> synapses_from_777 = net_builder.net->GetNeuron({5, 5, 5})->GetSynapsesByIndex({7, 7, 7});
  for (Synapse* s : synapses_from_777) {
    s->SetWeight(1.01f);
  }
  net_builder.AddMap({6, 6, 6}, {2, 2, 2}, {-5, 5, 5}, {2, 2, 2});
  net_builder.AddMap({-5, 5, 5}, {2, 2, 2}, {0, 0, 0}, {2, 2, 2});
  
  net = net_builder.net;
  nav_graph = net_builder.nav_graph;

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
  for (Neuron* n : net->GetNeurons()) {
    if (n->EnergyIsAboveThreshold()) {
      DrawNeuronFiring(n->xyz);
    }
    else {
      DrawNeuronResting(n->xyz);
    }
  }

  for (Synapse* s : net->GetSynapses()) {
    if (s->from.EnergyIsAboveThreshold()) {
      DrawSynapse(s->from.xyz, s->to.xyz, {1.0f, 1.0f, 0.0f, 0.2f});
    }
    else {
      DrawSynapse(s->from.xyz, s->to.xyz, {0.5f, 0.5f, 0.5f, 0.05f});
    }
  }
}

void TickNet() {
  net->Tick();
}

#endif
