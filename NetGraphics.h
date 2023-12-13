
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
#include "Draw.h"

using namespace std;



/* Rendering + logic. */
void InitNet();
void TickNet();
void DrawNet();

/* User interaction. */
void Move(vector<int> xyz);
void Stimulate();
void Inhibit();

/* Helper functions. */
void DrawNeurons();
void DrawSynapses();
void DrawNavNodes();

#endif
