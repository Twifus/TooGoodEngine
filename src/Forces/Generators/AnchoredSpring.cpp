#include "Forces/Generators/AnchoredSpring.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			AnchoredSpring::AnchoredSpring(Vector3 point, double k, double length) :
				anchor(point), k(k), length(length) {}

			void AnchoredSpring::UpdateForce(RigidBody& rb, double time) const
			{
				Vector3 direction = (rb.GetPosition() - anchor);
				rb.AddForce(-k * (direction.Magnitude() - length) * direction.Normalized());
			}
		}
	}
}