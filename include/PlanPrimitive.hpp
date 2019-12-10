#pragma once
#include "Primitive.hpp"

namespace TooGoodEngine 
{
	class PlanPrimitive : public Primitive
	{
	public:
		PRIMITIVE('PLAN')
	
	private:
		Vector3 normal;
		double offset;

	public:
		PlanPrimitive(const Vector3& normal, double offset);
		double DistanceToPlan(const Vector3& point) const;
		const Vector3& GetNormal() const;

	public:
		virtual std::vector<Contacts::Contact> ResolveCollision(const Primitive& other) const override;
	};
}
