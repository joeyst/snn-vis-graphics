
#include "Neuron.h" 
#include "utils.h"
#include "config.h"
#include <iostream>

Neuron::Neuron(float initialEnergy): energy(initialEnergy), fires(new Fires(N_TICKS_TO_TRACK)) {}
Neuron::Neuron(): energy(0.f), fires(new Fires(N_TICKS_TO_TRACK)) {}

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

bool Neuron::FiredFlag() {
  return this->firing;
}

void Neuron::AddAssignIncomingEnergy() {
  this->energy = this->energy + GetIncomingEnergy();
}

void Neuron::ApplyOjas() {
  if (EnergyIsAboveThreshold()) {
    for (Synapse* s : synapses) {
      float streng;
      float forget = s->GetWeight();
      if (s->from.FiredFlag()) {
        streng = 1.f;
      }
      else {
        streng = 0.f;
      }
      s->SetWeight(s->GetWeight() + (LEARNING_RATE * (streng + forget)));
    }
  }
}

void Neuron::PushFiringToBuffer() {
  fires->Push(FiredFlag());
  firing = false; // shouldn't be necessary but just in case. 
}

float Neuron::GetRawIncomingEnergy() {
  float res = 0.f;
  for (Synapse* s : synapses) {
    if (s->from.FiredFlag()) {
      res += s->GetWeight();
    }
  }
  return res;
}

float Neuron::GetIncomingEnergy() {
  return GetRawIncomingEnergy() * GetTolFactor();
}

int Neuron::NumberOfFires() {
  int number_of_fires = 0;
  for (std::size_t i = 0; i < this->fires->GetVector().size(); ++i) {
    if (this->fires->GetVector()[i]) {
      number_of_fires++;
    }
  }
  return number_of_fires;
}

float Neuron::GetTolFactor() {
  return ::GetTolFactor(this->NumberOfFires());
}

void Neuron::AddSynapse(Synapse* synapse) {
  synapses.push_back(synapse);
}

void Neuron::AddOutgoingSynapse(Synapse* synapse) {
  outgoing_synapses.push_back(synapse);
}

void Neuron::Print() {
  std::cout << "Neuron ==== " << std::endl;
  std::cout << "Energy: " << this->energy << std::endl;
  std::cout << "Synapses: " << std::endl;
  for (auto synapse : synapses) {
    std::cout << "  " << synapse->from.xyz[0] << " " << synapse->from.xyz[1] << " " << synapse->from.xyz[2] << "=>" << synapse->to.xyz[0] << " " << synapse->to.xyz[1] << " " << synapse->to.xyz[2] << " w: " << synapse->GetWeight() << std::endl;
  }
}

std::vector<Synapse*> Neuron::GetSynapsesByIndex(std::vector<int> xyz_) {
  std::vector<Synapse*> synapses_(0);
  for (Synapse* s : synapses) {
    if (s->from.xyz == xyz_) {
      synapses_.push_back(s);
    }
  }
  return synapses_;
}
