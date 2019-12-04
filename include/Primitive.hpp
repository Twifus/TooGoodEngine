#pragma once
#include "Matrix4.hpp"
#include "RigidBody.hpp"

namespace TooGoodEngine {
	class Primitive {
	public:
		RigidBody& rigidBody;
		Matrix4& transformation;

		Primitive(RigidBody& RigidBody, Matrix4& matrix);
		~Primitive();
	};
}
