
#include "utils.h"
#include <vector>
#include "ctest.h" 
#include <iostream>
#include "Block.h"
#include "Neuron.h"
#include "Net.h"
#include "NetBuilder.h"

#ifdef CTEST_ENABLE 

void TestGetOjaWeightChange() {
  std::vector<float> energies { 1.f, 1.f, 1.f };
  std::vector<float> weights { 0.1f, 0.2f, 0.2f };
  std::vector<float> expected { 0.475f, 0.450f, 0.450f };
  std::vector<float> actual = GetOjaWeightChanges(energies, weights);

  CTEST_ASSERT(expected == GetOjaWeightChanges(energies, weights), "3 neurons");
  
  std::cout << "Actual: ";
  for (const auto& result : actual) {
    std::cout << result << " ";
  }
  std::cout << std::endl;
  std::cout << "Expected: ";
  for (const auto& result : expected) {
    std::cout << result << " ";
  }
  std::cout << std::endl;
}

void TestNetBuilderAddRectangle() {
  NetBuilder net_builder;
  net_builder.AddRectangle({0, 0, 0}, {1, 1, 1}, {1, 1, 1}, 3);
  net_builder.net.neuron_id_map[{0, 0, 0}]->energy = 1.01f;
  Synapse* synapse = net_builder.net.neuron_id_map[{1, 1, 1}]->synapses[0];
  synapse->SetWeight(1.01f);

  net_builder.net.Print();

  for (int l = 0; l < 3; l++) {
    net_builder.net.Tick();
    net_builder.net.Print();
  }

  std::cout << "GetTolFactor(0): " << GetTolFactor(0) << std::endl;
}

int main(void)
{
    CTEST_VERBOSE(1);
    CTEST_COLOR(1);

    //TestGetOjaWeightChange();
    TestNetBuilderAddRectangle();

    CTEST_RESULTS();

    CTEST_EXIT();
}
#endif
