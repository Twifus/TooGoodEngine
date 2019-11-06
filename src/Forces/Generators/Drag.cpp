#include "Forces/Generators/Drag.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Drag::Drag(double k1, double k2) : k1(k1), k2(k2) {}

			void Drag::UpdateForce(Particle& particle, double time) const
			{
				if (particle.GetVelocity() != Vector3::zero)
					particle.AddForce(-(k1 * particle.GetVelocity().Magnitude() + k2 * particle.GetVelocity().SquaredMagnitude()) * particle.GetVelocity().Normalized());
			}
		}
	}
}
