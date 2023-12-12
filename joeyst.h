
/* Joey's globals, function decls., defines, includes. */
#include "InitNet.h"

typedef float Proportion;
using namespace std;
#include <vector>
#include <math.h>
#include <iostream>
#include <cmath> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

const float SPHERE_RADIUS  = 0.5f;
const int   SPHERE_SLICES  = 8;
const int   SPHERE_STACKS  = 8;

const float NEURON_RADIUS  = SPHERE_RADIUS;
const float NEURON_SPACING = 5.f * NEURON_RADIUS; 
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

/* End of Joey's globals, function decls., defines, includes. */
