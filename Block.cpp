
#include "Block.h"
#include "config.h"

Block::Block() {
  NeuronMatrix neurons(LAYERS_PER_BLOCK, std::vector<Neuron>(NEURONS_PER_LAYER));
}
