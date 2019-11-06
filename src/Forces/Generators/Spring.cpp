#include "Forces/Generators/Spring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Spring::Spring(Particle& particle, double k, double length) :
				extremeParticle(particle), k(k), length(length) {}

			void Spring::UpdateForce(Particle& particle, double time) const
			{
				Vector3 direction = (particle.position - extremeParticle.position);
				particle.AddForce(-k * (direction.Magnitude() - length) * direction.Normalized());
			}
		}
	}
}
