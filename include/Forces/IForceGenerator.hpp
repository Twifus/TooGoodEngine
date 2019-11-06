#pragma once

#include "Particle.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		class IForceGenerator
		{
		public:
			virtual ~IForceGenerator() = default;
			virtual void UpdateForce(Particle& particle, double time) const = 0;
		};
	}
}

