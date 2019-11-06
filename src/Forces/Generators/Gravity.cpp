#include "Forces/Generators/Gravity.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Vector3 Gravity::gravity = -10 * Vector3::up;

			void Gravity::UpdateForce(Particle& particle, double time) const
			{
				if (particle.GetMass() != 0)
				{
					particle.AddForce(particle.GetMass() * gravity);
				}
			}
		}
	}
}
