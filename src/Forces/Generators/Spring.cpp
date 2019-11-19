#include "Forces/Generators/Spring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Spring::Spring(Vector3& pos1, RigidBody& other, Vector3& pos2, double k, double length) :
				other(other), k(k), length(length) {}

			void Spring::UpdateForce(RigidBody& rb, double time) const
			{
				Vector3 direction = (rb.position - other.position);
				rb.AddForce(-k * (direction.Magnitude() - length) * direction.Normalized());
			}
		}
	}
}
