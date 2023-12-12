
#ifndef _SYNAPSE_H
#define _SYNAPSE_H

#include <vector>
#include "CircularBuffer.h"

class Neuron;
typedef CircularBuffer<float> Weights;
typedef std::size_t Index;

class Synapse {
  public:
    Neuron& from;
    Neuron& to;
    Weights weights;
    bool is_firing;

  public:
    Synapse(Neuron& from, Neuron& to, std::size_t n_last_weights_to_store);
    Synapse(Neuron& from, Neuron& to);
    float GetWeight();
    void  SetWeight(float weight);
    void OverwriteWeight(float weight);
};

#endif
