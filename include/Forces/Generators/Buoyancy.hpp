#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{

	namespace Forces
	{
		namespace Generators
		{
			class Buoyancy : public IForceGenerator
			{
			private:
				double maxDepth, volume, liquidHeight, density;

			public:
				Buoyancy(double maxDepth, double volume, double liquidHeight, double density);
				virtual void UpdateForce(RigidBody& rb, double time) const;
			};
		}
	}
}