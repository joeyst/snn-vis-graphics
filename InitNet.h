
#ifndef _INIT_NET_H
#define _INIT_NET_H

#include "utils.h"
#include <vector>
#include "ctest.h" 
#include <iostream>
#include "Block.h"
#include "Neuron.h"
#include "Net.h"
#include "NetBuilder.h"

NetBuilder net_builder;

void InitNet() {
  net_builder.AddRectangle({0, 0, 0}, {1, 1, 1}, {1, 1, 1}, 3);
  net_builder.net.neuron_id_map[{0, 0, 0}]->energy = 1.01f;
  Synapse* synapse = net_builder.net.neuron_id_map[{1, 1, 1}]->synapses[0];
  synapse->SetWeight(1.01f);

  // net_builder.net.Print();

  // for (int l = 0; l < 3; l++) {
  //   net_builder.net.Tick();
  //   net_builder.net.Print();
  // }

  // std::cout << "GetTolFactor(0): " << GetTolFactor(0) << std::endl;
}

#endif
