#pragma once
#include "Matrix4.hpp"
#include "RigidBody.hpp"
#include "Contacts/BoundingSphere.hpp"

namespace TooGoodEngine {
	class Primitive {
	public:
		RigidBody& rigidBody;
		Contacts::BoundingSphere& boundingSphere;
		Matrix4& transformation;

		Primitive(RigidBody& RigidBody, Matrix4& matrix, Contacts::BoundingSphere& sphere);
		~Primitive();
	};
}
