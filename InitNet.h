
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
  net_builder.AddRectangle({0, 0, 0}, {2, 2, 2}, {2, 2, 2}, 4);
  net_builder.AddRectangle({0, 0, 0}, {2, 2, 2}, {0, 0, 2}, 5);
  net_builder.AddRectangle({0, 0, 8}, {2, 2, 2}, {-2, 0, 0}, 5);
  net_builder.AddRectangle({8, 0, 8}, {2, 2, 2}, {-1, 0, -1}, 10);
  net_builder.AddRectangle({-8, 0, 8}, {2, 2, 2}, {1, 0, -1}, 10);
  net_builder.AddRectangle({0, 0, 8}, {2, 2, 2}, {2, 2, 0}, 5);
  net_builder.AddRectangle({8, 8, 8}, {2, 2, 2}, {-2, -2, 0}, 5);
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
  net_builder.AddRectangle({7, 7, 7}, {2, 1, 2}, {1, 1, 1}, 2);
  net_builder.net->EnableSynapse({7, 7, 7}, {-5, 5, 5});
  net_builder.net->EnableSynapse({-5, 5, 5}, {0, 0, 0});
  net_builder.net->EnableSynapse({-5, 5, 5}, {3, 3, 3});

  
  
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
