
#ifndef _DRAW_H
#define _DRAW_H

#include "includes.h"

GLuint neuron;
GLuint synapse;
GLuint box;

void DrawNeuron(vector<int> xyz, vector<Proportion> rgba);
void DrawSynapse(vector<int> start, vector<int> end, vector<Proportion> rgba);
void DrawBox(vector<int> center, int r, vector<Proportion> rgba);

void InitNeuronDL();
void InitSynapseDL();
void InitBoxDL();

vector<float> GetSynapseDXYZ(vector<int> start, vector<int> end);
float GetSynapseLength(vector<int> start, vector<int> end);

#endif
