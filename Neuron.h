
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
  1. Iterate synapses, setting is_firing based on if current neuron energy exceeds threshold. 
  2. 

  OLD steps: 
  1. Set firing_next for each neuron, based on if current energy is above threshold. 
  2. Update all the synapses, based on the last tick's fire bool and firing_next. 
  3. Update the energies by setting to zero if the neuron fired, otherwise decaying and adding the energies from the current tick. 
  4. Push firing_next. 
  */
  public:
    float energy; 
    Fires fires;
    bool fired; 
    std::vector<Synapse*> synapses;
    PointIds3D xyz; 

  public:
    Neuron(float initialEnergy);
    Neuron();
    void UpdateSynapses();
    void UpdateEnergy();
    void AddSynapse(Synapse* synapse);
    void Print();

  private:
    bool EnergyExceedsFiringThreshold();
    void DecayEnergy();
    void ZeroEnergy();
    void ZeroEnergyIfExceeds();

    int NumberOfFires();
    void SetCurrentTickFire(bool did_fire);
    float GetTolFactor();

    float GetRawEnergyReceived();
    bool JustFired();
    float GetTolAdjustedEnergyReceived();

    void SetFired();
    float Output();
    void ApplyOjas();
  };

#endif 
