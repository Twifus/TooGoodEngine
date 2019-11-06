#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Particle.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			class AnchoredSpring : public IForceGenerator
			{
			private:
				Vector3 anchor;
				double k;
				double length;

			public:
				AnchoredSpring(Vector3 point, double k, double length);
				void UpdateForce(Particle& particle, double time) const;
			};
		}
	}
}