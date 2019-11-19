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
				RigidBody& other;
				double k;
				double length;

			public:
				BungeeSpring(RigidBody& other, double k, double length);
				void UpdateForce(RigidBody& rb, double time) const;
			};
		}
	}
}