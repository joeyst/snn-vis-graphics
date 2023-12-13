
#ifndef _CONFIG_H 
#define _CONFIG_H 
#include <cstddef>

const float NEURON_FIRE_THRESH = 1.f;
const float FIRING_RATE_GOAL   = 4.f; // Per 32 ticks. 
const int   LAYERS_PER_BLOCK   = 4;
const int   NEURONS_PER_LAYER  = 4;
const float LEARNING_RATE      = 0.01f;
const float ENERGY_DECAY_PROP  = 0.1f;
const std::size_t N_TICKS_TO_TRACK = 32;
const std::size_t N_LAST_WEIGHTS_TO_STORE = 32;

const float SPHERE_RADIUS  = 0.5f;
const int   SPHERE_SLICES  = 2;
const int   SPHERE_STACKS  = 2;

const float NEURON_RADIUS  = SPHERE_RADIUS;
const float NEURON_SPACING = 5.f * NEURON_RADIUS; 

const int BLOCK_SPACING = 7;

#endif 
