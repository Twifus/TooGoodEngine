#include "Forces/Generators/Drag.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Drag::Drag(double k1, double k2) : k1(k1), k2(k2) {}

			void Drag::UpdateForce(RigidBody& rb, double time) const
			{
				if (rb.GetVelocity() != Vector3::zero)
					rb.AddForce(-(k1 * rb.GetVelocity().Magnitude() + k2 * rb.GetVelocity().SquaredMagnitude()) * rb.GetVelocity().Normalized());
			}
		}
	}
}
