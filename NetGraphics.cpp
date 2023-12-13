
#include "NetGraphics.h"
#include "Draw.h"

NetBuilder* net_builder;
Net* net;
vector<vector<int>> NeuronCoordsList;

/* Rendering + logic. */
void InitNet() {
  net_builder = new NetBuilder();
  net_builder->AddBlock(std::vector<int> {0, 0, 0}, 2);
  // net_builder->AddBlock(std::vector<int> {0, 0, 0}, std::vector<int> {2, 2, 2}, std::vector<int> {2, 2, 2}, 4);
  /*
  net_builder->net->GetNeuron({0, 0, 0})->energy = 1.01f;
  net_builder->net->GetNeuron({3, 3, 3})->energy = 1.01f;
  Synapse* synapse = net_builder->net->GetNeuron({2, 2, 2})->synapses[0];
  for (Synapse* s : net_builder->net->GetNeuron({3, 3, 3})->synapses) {
    s->SetWeight(1.01f);
  }
  vector<Synapse*> synapses_from_777 = net_builder->net->GetNeuron({5, 5, 5})->GetSynapsesByIndex({7, 7, 7});
  for (Synapse* s : synapses_from_777) {
    s->SetWeight(1.01f);
  }
  net_builder->AddMap({6, 6, 6}, {2, 2, 2}, {-5, 5, 5}, {2, 2, 2});
  net_builder->AddMap({-5, 5, 5}, {2, 2, 2}, {0, 0, 0}, {2, 2, 2});
  
  */
  net = net_builder->net;
}

void TickNet() {
  net->Tick();
}

void DrawNet() {
  DrawNeurons();
  DrawSynapses();
}

/* User interaction. */

/* Helper functions. */

void DrawNeurons() {
  for (Neuron* n : net->GetNeurons()) {
    if (n->EnergyIsAboveThreshold()) {
      DrawNeuronFiring(n->xyz);
    }
    else {
      DrawNeuronResting(n->xyz);
    }
  }
}

void DrawSynapses() {
  for (Synapse* s : net->GetSynapses()) {
    if (s->from.EnergyIsAboveThreshold()) {
      DrawSynapse(s->from.xyz, s->to.xyz, {1.0f, 1.0f, 0.0f, 0.2f});
    }
    else {
      DrawSynapse(s->from.xyz, s->to.xyz, {0.5f, 0.5f, 0.5f, 0.05f});
    }
  }
}
