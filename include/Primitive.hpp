#pragma once
#include "Transform.hpp"
#include "RigidBody.hpp"
#include "Contacts/BoundingSphere.hpp"

namespace TooGoodEngine {
	class Primitive {
	public:
		RigidBody& rigidBody;																			//RigidBody which the primitive is associated to
		Contacts::BoundingSphere boundingSphere;														//BoundingSphere of the primitive
		Transform transformation;																		//Deformation due to a collision

		Primitive(RigidBody& RigidBody, Transform& transform, Contacts::BoundingSphere& sphere);		//Primitive constructor
		~Primitive();																					//Primitive destructor
	};
}
