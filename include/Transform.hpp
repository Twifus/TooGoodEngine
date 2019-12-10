#pragma once

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix3.hpp"

namespace TooGoodEngine {
	class Transform
	{
	public:
		static const Transform identity;

		Transform();	// Construct a transform with default rotation and position
		Transform(const Vector3 &v, const Quaternion& q = Quaternion::identity);		// Construct a matrix from a Quaternion and a Vector

		bool operator==(const Transform& matrix) const;			// Comparison of the two matrix component by component
		bool operator!=(const Transform& matrix) const;			// Comparison like above

		Vector3 operator*(const Vector3& vector) const;			// Multiplication of a matrix with a Vector				return a new Vector
		Transform operator*(const Transform& matrix) const;		// Multiplication of two matrix							return a new one

		Transform& operator*=(const Transform& transform);			// Multiplication of this with another matrix			return modified matrix

		Transform Inverse() const;

		const Vector3& GetPosition() const;
		const Quaternion& GetRotation() const;

	private:
		Vector3 position;
		Quaternion rotation;
	};
}