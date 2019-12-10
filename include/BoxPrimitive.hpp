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
		Vector3 size;

	public:
		BoxPrimitive(RigidBody* rigidbody, Vector3& size);

		virtual std::vector<Contacts::Contact> ResolveCollision(const Primitive& other) const override;
	};
}
