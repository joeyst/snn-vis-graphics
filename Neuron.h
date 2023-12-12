
#ifndef _NEURON_H
#define _NEURON_H 

#include <cstdint>
#include <vector>
#include "Point3D.h"
#include "Synapse.h"
#include "CircularBuffer.h"

typedef CircularBuffer<bool> Fires;

class Neuron {
  /* 
  energy | Current energy of neuron. 
  fires | Last N ticks bools. 
  firing_next | If firing during current tick. 

  STEPS:
  Starts with energies before firing+zeroing xor decaying. 
  1. Set flag variable for if neuron exceeds energy thresh. 
  2. For neurons that *are* firing atm, set energy to zero. Else, decay. 
  3. Collect (and add) energies from previous neurons, using the flag variable that was set. 
  4. Check if neuron exceeds energy thresh. If it does, apply Oja's. Otherwise, do nothing, because the output in Oja's rule will be zero. 
    1. The synapse uses a circular buffer to store the previous weights. 
  5. Push flag variable to circular buffer for firing, so that tolerance in step 3 can be calculated. 
  6. Return to step 1. 

  The functions for each of the steps are: 
  1. SetFiredFlag. 
  2. ZeroOrDecayEnergy. 
  3. AddAssignIncomingEnergy.
  4. ApplyOjas. 
  5. PushFiringToBuffer. 
  */
  public:
    float energy; 
    Fires *fires;
    bool firing; 
    std::vector<Synapse*> synapses;
    std::vector<Synapse*> outgoing_synapses;
    PointIds3D xyz; 

  public:
    Neuron(float initialEnergy);
    Neuron();

    // Stimulation interface: 
    void SetFiredFlag();

    // Net modification interface: 
    void AddSynapse(Synapse* synapse);
    void AddOutgoingSynapse(Synapse* synapse);

    // Stages interface: 
    void SetFiredFlag();
    void ZeroOrDecayEnergy();
    void AddAssignIncomingEnergy();
    void ApplyOjas();
    void PushFiringToBuffer();

    // Debug interface: 
    void Print();

    // Primarily for inner logic, but can use outside: 
    float GetIncomingEnergy();

  private:
    bool EnergyIsAboveThreshold();
    float GetRawIncomingEnergy();
    bool FiredFlag();
    int NumberOfFires();
    float GetTolFactor();
  };

#endif 
