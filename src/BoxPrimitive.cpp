#include <array>
#include <cmath>
#include <iostream>
#include "BoxPrimitive.hpp"
#include "Contacts/Contact.hpp"
#include "PlanPrimitive.hpp"

namespace TooGoodEngine
{
	BoxPrimitive::BoxPrimitive(RigidBody& rigidbody,  Vector3& halfSize) : rigidBody(rigidbody), halfSize(halfSize) {}

	std::vector<Contacts::Contact> BoxPrimitive::ResolveCollision(const Primitive& other) const
	{
		if (other.GetUID() == PlanPrimitive::primitiveUID)
		{
			std::vector<Contacts::Contact> res;
			auto plan = reinterpret_cast<const PlanPrimitive&>(other);
			std::array<Vector3, 8> directions
			{
				Vector3( 1,  1,  1),
				Vector3(-1,  1,  1),
				Vector3( 1, -1,  1),
				Vector3( 1,  1, -1),
				Vector3(-1, -1,  1),
				Vector3(-1,  1, -1),
				Vector3( 1, -1, -1),
				Vector3(-1, -1, -1)
			};
			for (Vector3 dir : directions)
			{
				Vector3 vertex = rigidBody.GetOrientation() * (dir * halfSize) + rigidBody.GetPosition();
				double dist = plan.DistanceToPlan(vertex);
				if (dist <= 0)
				{
					res.emplace_back(vertex, plan.GetNormal(), std::abs(dist));
				}
			}
			return res;
		}
		else
		{
			//std::cerr << "WARNING - Contact resolution between primitives '" << GetUID() << "' and '" << other.GetUID() << "' is not implemented" << std::endl;
		}

		return std::vector<Contacts::Contact>();
	}
}