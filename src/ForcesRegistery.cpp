#include "ForcesRegistery.hpp"

namespace TooGoodEngine
{
	ForcesRegistery::RegistryEntry::RegistryEntry(Particle& particle, ParticleForceGenerator& generator) : particle(particle), generator(generator) {}

	void ForcesRegistery::Add(Particle& particle, ParticleForceGenerator& generator)
	{
		registry.push_back(ForcesRegistery::RegistryEntry(particle, generator));
	}

	void ForcesRegistery::Clear()
	{
		registry.clear();
	}
}