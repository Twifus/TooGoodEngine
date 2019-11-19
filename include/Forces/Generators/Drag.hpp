#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			class Drag : public IForceGenerator
			{
			private:
				double k1, k2;

			public:
				Drag(double k1, double k2);
				void UpdateForce(RigidBody& rb, double time) const;
			};
		}
	}
}