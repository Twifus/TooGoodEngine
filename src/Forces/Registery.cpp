#include "Forces/Registery.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		Registery::RegistryEntry::RegistryEntry(Particle& particle, IForceGenerator& generator) : particle(particle), generator(generator) {}

		void Registery::Add(Particle& particle, IForceGenerator& generator)
		{
			registry.push_back(Registery::RegistryEntry(particle, generator));
		}

		void Registery::UpdateForces(double time)
		{
			for (RegistryEntry entry : registry)
			{
				entry.generator.UpdateForce(entry.particle, time);
			}
		}

		void Registery::Clear()
		{
			registry.clear();
		}
	}
}