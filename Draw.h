
#ifndef _DRAW_H
#define _DRAW_H

#include "includes.h"
#include "config.h"

/* Drawing Neurons, Synapses, and Boxes. */
void DrawNeuron(vector<int> xyz, vector<Proportion> rgba);
void DrawNeuronFiring(vector<int> xyz);
void DrawNeuronResting(vector<int> xyz);
void DrawSynapse(vector<int> start, vector<int> end, vector<Proportion> rgba);
void DrawBox(vector<int> center, int r, vector<Proportion> rgba);

/* Initializing display lists. */
void InitNeuronDL();
void InitSynapseDL();
void InitBoxDL();

/* Synapse rotation logic. */
vector<float> GetCoordsFromPoint(vector<int> point);
float EuclidianNorm(vector<float> point);
vector<float> sub(vector<float> start, vector<float> end);

#endif
