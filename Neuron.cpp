
#include "Neuron.h" 
#include "utils.h"
#include "config.h"
#include <iostream>

Neuron::Neuron(float initialEnergy): energy(initialEnergy), fires(Fires(N_TICKS_TO_TRACK)) {}
Neuron::Neuron(): energy(0.f), fires(Fires(N_TICKS_TO_TRACK)) {}

void Neuron::SetFiredFlag() {
  this->firing = EnergyIsAboveThreshold();
}

bool Neuron::EnergyIsAboveThreshold() {
  return this->energy > NEURON_FIRE_THRESH;
}

void Neuron::ZeroOrDecayEnergy() {
  if (EnergyIsAboveThreshold()) {
    energy = 0.f;
  }
  else {
    energy = (1 - ENERGY_DECAY_PROP) * energy;
  }
}

float Neuron::GetRawIncomingEnergy() {

}



int Neuron::NumberOfFires() {
  int number_of_fires = 0;
  for (std::size_t i = 0; i < this->fires.GetVector().size(); ++i) {
    if (this->fires.GetVector()[i]) {
      number_of_fires++;
    }
  }
  return number_of_fires;
}

bool Neuron::EnergyExceedsFiringThreshold() {
  return this->energy > NEURON_FIRE_THRESH;
}

float Neuron::GetTolFactor() {
  return ::GetTolFactor(this->NumberOfFires());
}

void Neuron::DecayEnergy() {
  this->energy = (1.f - ENERGY_DECAY_PROP) * this->energy;
}

void Neuron::ZeroEnergy() {
  this->energy = 0.f;
}

void Neuron::UpdateEnergy() {
  fires.Push(firing);
  if (firing) {
    energy = 0.f;
  }
  else {
    energy += GetTolAdjustedEnergyReceived();
    DecayEnergy();
  }
}

float Neuron::GetRawEnergyReceived() {
  float e = 0.f;
  for (auto synapse : synapses) {
    if (synapse->from.JustFired()) {
      e += synapse->GetWeight();
    }
  }
  return e;
}

bool Neuron::JustFired() {
  return this->fires.Peek();
}

float Neuron::GetTolAdjustedEnergyReceived() {
  Print();
  std::cout << "Raw Energy Received * Tol Factor: " << GetRawEnergyReceived() * GetTolFactor() << std::endl;
  return GetRawEnergyReceived() * GetTolFactor();
}

void Neuron::SetFired() {
  if (energy + GetTolAdjustedEnergyReceived() > NEURON_FIRE_THRESH) {
    firing = true;
  }
}

float Neuron::Output() {
  if (firing) {
    return 1.f;
  }
  else {
    return 0.f;
  }
}

void Neuron::ApplyOjas() {
  for (auto synapse : synapses) {
    float streng = synapse->from.JustFired() * Output();
    float forget = synapse->GetWeight() * Output() * Output();
    float change = (streng - forget) * LEARNING_RATE;
    synapse->SetWeight(synapse->GetWeight() + change);
  }
}

void Neuron::UpdateSynapses() {
  SetFired();
  ApplyOjas();
}

void Neuron::AddSynapse(Synapse* synapse) {
  synapses.push_back(synapse);
}

void Neuron::Print() {
  std::cout << "Neuron ==== " << std::endl;
  std::cout << "Energy: " << this->energy << std::endl;
  std::cout << "Synapses: " << std::endl;
  for (auto synapse : synapses) {
    std::cout << "  " << synapse->from.xyz[0] << " " << synapse->from.xyz[1] << " " << synapse->from.xyz[2] << "=>" << synapse->to.xyz[0] << " " << synapse->to.xyz[1] << " " << synapse->to.xyz[2] << " w: " << synapse->GetWeight() << std::endl;
  }
}
