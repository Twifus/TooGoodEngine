#pragma once

#include <vector>
#include "Particle.hpp"
#include "ParticleForceGenerator.hpp"

namespace TooGoodEngine
{
	class ForcesRegistery
	{
	private:
		struct RegistryEntry
		{
			Particle& particle;
			ParticleForceGenerator &generator;

			RegistryEntry(Particle& particle, ParticleForceGenerator& generator);
		};

		std::vector<RegistryEntry> registry;

	public:
		void Add(Particle& particle, ParticleForceGenerator& generator);
		void Clear();
	};
}