#include "Forces/Generators/BungeeSpring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			BungeeSpring::BungeeSpring(RigidBody& other, double k, double length) :
				other(other), k(k), length(length) {}

			void BungeeSpring::UpdateForce(RigidBody& rb, double time) const
			{
				Vector3 direction = (rb.position - other.position);
				double appliedLength = direction.Magnitude();
				if (appliedLength > length)
					rb.AddForce(-k * (appliedLength - length) * direction.Normalized());
			}
		}
	}
}