#pragma once

#include <vector>
#include "Particle.hpp"
#include "ParticleForceGenerator.hpp"

namespace TooGoodEngine
{
	class ForcesRegistery
	{
	private:
		struct ForcesRegistryEntry
		{
			Particle& particle;
			ParticleForceGenerator &generator;

			ForcesRegistryEntry(Particle& particle, ParticleForceGenerator& generator);
		};

		std::vector<ForcesRegistryEntry> registry;

	public:
		void Add(Particle& particle, ParticleForceGenerator& generator);
		void Clear();
	};
}