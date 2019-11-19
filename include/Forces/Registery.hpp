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
				RigidBody& particle;
				IForceGenerator& generator;

				RegistryEntry(RigidBody& particle, IForceGenerator& generator);
			};

			std::vector<RegistryEntry> registry;

		public:
			void Add(RigidBody& particle, IForceGenerator& generator);
			void UpdateForces(double time);
			void Clear();
		};
	}
}