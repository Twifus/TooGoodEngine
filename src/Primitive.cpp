#include "Primitive.hpp"

namespace TooGoodEngine {

	Primitive::Primitive(RigidBody& RigidBody, Matrix4& matrix, Contacts::BoundingSphere& sphere) : rigidBody(RigidBody), transformation(matrix), boundingSphere(sphere) {}

	Primitive::~Primitive() {}
}