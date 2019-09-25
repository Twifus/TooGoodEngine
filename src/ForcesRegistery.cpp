#include "ForcesRegister.hpp"
#include "..\include\ForcesRegistery.hpp"

TooGoodEngine::ForcesRegistery::ForcesRegistryEntry::ForcesRegistryEntry(Particle & particle, ParticleForceGenerator & generator) : particle(particle), generator(generator) {}

void TooGoodEngine::ForcesRegistery::Add(Particle & particle, ParticleForceGenerator & generator)
{
	//registry.add
}

void TooGoodEngine::ForcesRegistery::Clear()
{
	registry.clear();
}
