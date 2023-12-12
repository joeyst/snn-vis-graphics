
#include "Neuron.h"
#include <vector>
#include <utility>

#ifndef _BLOCK_H
#define _BLOCK_H

typedef int BlockId;
typedef std::vector<std::vector<Neuron>> NeuronMatrix;

class Block {
  public: 
    Block();
    NeuronMatrix neurons;

  //private:
  //  std::vector<std::pair<BlockId, > recvs
};

#endif 
