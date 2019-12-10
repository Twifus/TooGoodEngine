#include "Transform.hpp"

namespace TooGoodEngine
{
	const Transform Transform::identity(Vector3::zero, Quaternion::identity);

	Transform::Transform() : Transform(Vector3::zero, Quaternion::identity) {};

	Transform::Transform(const Vector3& v, const Quaternion& q) : position(v), rotation(q.Normalized()) {}

	bool Transform::operator==(const Transform& matrix) const {
		return (position == matrix.position && rotation == matrix.rotation);
	}

	bool Transform::operator!=(const Transform& matrix) const {
		return !((*this) == matrix);
	}

	Vector3 Transform::operator*(const Vector3& vector) const {
		return rotation * vector + position;
	}

	Transform Transform::operator*(const Transform& matrix) const {
		return Transform(position + matrix.position, (rotation * matrix.rotation).Normalized());
	}

	Transform& Transform::operator*=(const Transform& matrix) {
		return ((*this) = (*this) * matrix);
	}

	Transform Transform::Inverse() const {
		return Transform(-position, rotation.Inverse().Normalized());
	}

	const TooGoodEngine::Vector3& Transform::GetPosition() const
	{
		return position;
	}

	const TooGoodEngine::Quaternion& Transform::GetRotation() const
	{
		return rotation;
	}
}