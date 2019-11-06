#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			class BungeeSpring : public IForceGenerator
			{
			private:
				Particle& extremeParticle;
				double k;
				double length;

			public:
				BungeeSpring(Particle& particle, double k, double length);
				void UpdateForce(Particle& particle, double time) const;
			};
		}
	}
}