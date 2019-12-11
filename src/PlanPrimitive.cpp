#include <iostream>
#include "BoxPrimitive.hpp"
#include "PlanPrimitive.hpp"

namespace TooGoodEngine
{
	PlanPrimitive::PlanPrimitive(const Vector3& normal, double offset) : normal(normal.Normalized()), offset(offset) {}

	double PlanPrimitive::DistanceToPlan(const Vector3& point) const
	{
		return normal.Dot(point) + offset;
	}

	const Vector3& PlanPrimitive::GetNormal() const
	{
		return normal;
	}

	std::vector<Contacts::Contact> PlanPrimitive::ResolveCollision(const Primitive& other) const
	{
		if (other.GetUID() == BoxPrimitive::primitiveUID)
		{
			auto box = reinterpret_cast<const BoxPrimitive&>(other);
			return box.ResolveCollision(*this);
		}
		else
		{
			//std::cerr << "WARNING - Contact resolution between primitives '" << GetUID() << "' and '" << other.GetUID() << "' is not implemented" << std::endl;
		}

		return std::vector<Contacts::Contact>();
	}
}