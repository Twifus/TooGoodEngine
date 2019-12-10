#pragma once
#include "Transform.hpp"
#include "RigidBody.hpp"
#include "Contacts/BoundingSphere.hpp"

namespace TooGoodEngine {
	class Primitive {
	public:
		RigidBody& rigidBody;
		Contacts::BoundingSphere boundingSphere;
		Transform transformation;

		Primitive(RigidBody& RigidBody, Transform& transform, Contacts::BoundingSphere& sphere);
		~Primitive();
	};
}
