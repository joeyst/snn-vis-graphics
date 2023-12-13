
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

NetBuilder* net_builder;
Net* net;
NavGraph* nav_graph;
vector<vector<int>> NeuronCoordsList;

void InitNet();

typedef float Proportion;
void DrawNeuron(vector<int> xyz, vector<Proportion> rgba);
void DrawSynapse(vector<int> start, vector<int> end, vector<Proportion> rgba);

void DrawNeuronFiring(vector<int> xyz) {
  DrawNeuron(xyz, { 1.0f, 1.0f, 0.0f, 0.7f });
}

void DrawNeuronResting(vector<int> xyz) {
  DrawNeuron(xyz, { 0.5f, 0.5f, 0.5f, 0.3f });
}

void DrawNet();

void TickNet();

void Move(vector<int> xyz);

void Stimulate();

void Inhibit();

#endif
