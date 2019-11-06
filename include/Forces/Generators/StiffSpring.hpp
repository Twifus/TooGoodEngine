#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			class StiffSpring : public IForceGenerator
			{
			private:
				Vector3 anchor;
				double k;
				double damping;

			public:
				StiffSpring(Vector3 anchor, double k, double damping);
				void UpdateForce(Particle& particle, double time) const;
			};
		}
	}
}