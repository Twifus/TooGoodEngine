#include "Forces/Generators/BungeeSpring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			BungeeSpring::BungeeSpring(Particle& particle, double k, double length) :
				extremeParticle(particle), k(k), length(length) {}

			void BungeeSpring::UpdateForce(Particle& particle, double time) const
			{
				Vector3 direction = (particle.position - extremeParticle.position);
				double appliedLength = direction.Magnitude();
				if (appliedLength > length)
					particle.AddForce(-k * (appliedLength - length) * direction.Normalized());
			}
		}
	}
}