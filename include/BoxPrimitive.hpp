#pragma once
#include "Primitive.hpp"

namespace TooGoodEngine
{
	class BoxPrimitive : public Primitive
	{
	public:
		PRIMITIVE('BOX')

	private:
		RigidBody* rigidBody;
		Vector3 halfSize;

	public:
		BoxPrimitive(RigidBody* rigidbody, Vector3& halfSize);

		virtual std::vector<Contacts::Contact> ResolveCollision(const Primitive& other) const override;
	};
}
