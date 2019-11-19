#include "Forces/Generators/Gravity.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Vector3 Gravity::gravity = -10 * Vector3::up;

			void Gravity::UpdateForce(RigidBody& rb, double time) const
			{
				if (rb.GetMass() != 0)
				{
					rb.AddForce(rb.GetMass() * gravity);
				}
			}
		}
	}
}
