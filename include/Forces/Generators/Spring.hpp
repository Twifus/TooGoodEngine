#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			class Spring : public IForceGenerator
			{
			private:
				Particle& extremeParticle;
				double k;
				double length;

			public:
				Spring(Particle& particle, double k, double length);
				void UpdateForce(Particle& particle, double time) const;
			};
		}
	}
}