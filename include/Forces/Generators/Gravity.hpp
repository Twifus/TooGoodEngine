#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			class Gravity : public IForceGenerator
			{
			private:
				static Vector3 gravity;

			public:
				Gravity() = default;
				void UpdateForce(Particle& particle, double time) const;
			};
		}
	}
}

