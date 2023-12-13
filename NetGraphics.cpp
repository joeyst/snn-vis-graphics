
#include "NetGraphics.h"
#include "Draw.h"

NetBuilder* net_builder;
Net* net;
NavGraph* nav_graph;
vector<vector<int>> NeuronCoordsList;

/* Rendering + logic. */
void InitNet() {
  nav_graph = new NavGraph();

  net_builder = nav_graph->net_builder;
  net_builder->AddRectangle({0, 0, 0}, {2, 2, 2}, {2, 2, 2}, 4);
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
  
  net = net_builder->net;
}

void TickNet() {
  net->Tick();
}

void DrawNet() {
  DrawNeurons();
  DrawSynapses();
  DrawNavNodes();
}

/* User interaction. */
void Move(vector<int> xyz) {
  nav_graph->Move(xyz);
}

void Stimulate() {
  nav_graph->Stimulate();
}

void Inhibit() {
  nav_graph->Inhibit();
}

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

void DrawNavNodes() {
  for (NavNode* n : nav_graph->GetNavNodes()) {
    if (n == nav_graph->GetCurrentNode()) {
      DrawBox(n->xyz_id, n->r, {0.0f, 1.0f, 0.0f, 0.2f});
    }
    else {
      DrawBox(n->xyz_id, n->r, {0.0f, 0.0f, 1.0f, 0.1f});
    }
  }
}
