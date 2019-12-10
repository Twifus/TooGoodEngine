#include "Primitive.hpp"

namespace TooGoodEngine {

	Primitive::Primitive(RigidBody& RigidBody, Transform& matrix, Contacts::BoundingSphere& sphere) : rigidBody(RigidBody), transformation(matrix), boundingSphere(sphere) {}

	Primitive::~Primitive() {}
}