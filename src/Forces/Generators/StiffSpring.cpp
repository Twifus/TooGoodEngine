#include "Forces/Generators/StiffSpring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			StiffSpring::StiffSpring(Vector3 anchor, double k, double damping) :
				anchor(anchor), k(k), damping(damping) {}

			void StiffSpring::UpdateForce(Particle& particle, double time) const
			{
				Vector3 position = (particle.position - anchor);
				Vector3 direction = position.Normalized();
				Vector3 projectedVelocity = (particle.GetVelocity()).Dot(direction) * direction;
				particle.AddForce(-k * position - damping * projectedVelocity);
			}
		}
	}
}
