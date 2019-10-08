#include "ForcesRegistery.hpp"

namespace TooGoodEngine
{
	ForcesRegistery::RegistryEntry::RegistryEntry(Particle& particle, ParticleForceGenerator& generator) : particle(particle), generator(generator) {}

	void ForcesRegistery::Add(Particle& particle, ParticleForceGenerator& generator)
	{
		registry.push_back(ForcesRegistery::RegistryEntry(particle, generator));
	}

	void ForcesRegistery::UpdateForces(double time)
	{
		for (RegistryEntry entry : registry)
		{
			entry.generator.UpdateForce(entry.particle, time);
		}
	}

	void ForcesRegistery::Clear()
	{
		registry.clear();
	}
}