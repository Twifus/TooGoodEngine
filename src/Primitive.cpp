#include "Primitive.hpp"

namespace TooGoodEngine {

	Primitive::Primitive(RigidBody& RigidBody, Matrix4& matrix) : rigidBody(RigidBody), transformation(matrix) {}

	Primitive::~Primitive() {}
}