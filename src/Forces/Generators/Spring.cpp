#include "Forces/Generators/Spring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Spring::Spring(RigidBody& other, double k, double length) : Spring(Vector3::zero, other, Vector3::zero, k, length) {}

			Spring::Spring(const Vector3& pos1, RigidBody& other, const Vector3& pos2, double k, double length) :
				pos1(pos1), other(other), pos2(pos2), k(k), length(length) {}

			void Spring::UpdateForce(RigidBody& rb, double time) const
			{
				Vector3 direction = (rb.BodyToWorld(pos1) - other.BodyToWorld(pos2));
				rb.AddForceAtBodyPoint(-k * (direction.Magnitude() - length) * direction.Normalized(), pos1);
			}
		}
	}
}
