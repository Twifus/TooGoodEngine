#include "ForcesRegister.hpp"
#include "..\include\ForcesRegistery.hpp"

TooGoodEngine::ForcesRegistery::RegistryEntry::RegistryEntry(Particle & particle, ParticleForceGenerator & generator) : particle(particle), generator(generator) {}

void TooGoodEngine::ForcesRegistery::Add(Particle & particle, ParticleForceGenerator & generator)
{
	registry.push_back(ForcesRegistery::RegistryEntry(particle, generator));
}

void TooGoodEngine::ForcesRegistery::Clear()
{
	registry.clear();
}
