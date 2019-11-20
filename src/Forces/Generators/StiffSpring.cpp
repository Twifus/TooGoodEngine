#include "Forces/Generators/StiffSpring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			StiffSpring::StiffSpring(Vector3 anchor, double k, double damping) :
				anchor(anchor), k(k), damping(damping) {}

			void StiffSpring::UpdateForce(RigidBody& rb, double time) const
			{
				Vector3 position = (rb.GetPosition() - anchor);
				Vector3 direction = position.Normalized();
				Vector3 projectedVelocity = (rb.GetVelocity()).Dot(direction) * direction;
				rb.AddForce(-k * position - damping * projectedVelocity);
			}
		}
	}
}
