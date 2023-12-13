
/* Joey's globals, function decls., defines, includes. */
#include "NetGraphics.h"

#include "includes.h"


GLuint neuron;
void InitNeuronDL();
void DrawNeuronf(vector<float> xyz, enum Colors color);
void DrawNeuronf(vector<float> xyz, enum Colors color, Proportion alpha);
vector<vector<int>> NeuronCoordsList;
void DrawNeuron(vector<int> xyz, enum Colors color, Proportion alpha);
void DrawNeuron(vector<int> xyz, vector<Proportion> rgba);

GLuint synapse;
void InitSynapseDL();
void DrawSynapse(vector<int> start, vector<int> end, vector<Proportion> rgba);
vector<float> GetSynapseDXYZ(vector<int> start, vector<int> end);
float GetSynapseLength(vector<int> start, vector<int> end);

GLuint box;
void InitBoxDL();
void DrawBox(vector<int> center, int r, vector<Proportion> rgba);

/* End of Joey's globals, function decls., defines, includes. */
