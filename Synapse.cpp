
#include "Synapse.h" 
#include "utils.h"
#include "config.h"
#include <iostream>

Synapse::Synapse(Neuron& from, Neuron& to, std::size_t n_last_weights_to_store) : from(from), to(to), weights(n_last_weights_to_store) {
  for (std::size_t i = 0; i < n_last_weights_to_store; i++) {
    weights.Push(0.0f);
  }
}

Synapse::Synapse(Neuron& from, Neuron& to) : Synapse(from, to, N_LAST_WEIGHTS_TO_STORE) {}

float Synapse::GetWeight() {
  return weights.Peek();
}

void Synapse::SetWeight(float weight) {
  weights.Push(weight);
}

void Synapse::OverwriteWeight(float weight) {
  weights.Overwrite(weight);
}
