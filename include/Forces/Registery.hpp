#pragma once

#include <vector>
#include "Forces/IForceGenerator.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		class Registery
		{
		private:
			struct RegistryEntry
			{
				Particle& particle;
				IForceGenerator& generator;

				RegistryEntry(Particle& particle, IForceGenerator& generator);
			};

			std::vector<RegistryEntry> registry;

		public:
			void Add(Particle& particle, IForceGenerator& generator);
			void UpdateForces(double time);
			void Clear();
		};
	}
}