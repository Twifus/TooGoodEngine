#pragma once

#include "Vector3.hpp"

#include <ostream>

namespace TooGoodEngine
{
	class Quaternion
	{
	public:
		double w, x, y, z;

		static const Quaternion identity;

		Quaternion();
		Quaternion(double w, double x, double y, double z);

		static Quaternion AxisAngle(const Vector3& axis, double angle);

		bool operator==(const Quaternion& other) const;
		bool operator!=(const Quaternion& other) const;

		Quaternion operator-() const;
		Quaternion operator+() const;

		Quaternion operator*(const Quaternion& other) const;

		Quaternion& operator*=(const Quaternion& other);

		double Dot(const Quaternion& other) const;

		Quaternion Normalized() const;
		double Magnitude() const;
		double SquaredMagnitude() const;

		Quaternion Inverted() const;
	};

	Quaternion operator*(const Quaternion& q, double k);
	Quaternion operator*(double k, const Quaternion& q);
	Quaternion operator/(const Quaternion& q, double k);

	Quaternion& operator*=(Quaternion& q, double k);
	Quaternion& operator/=(Quaternion& q, double k);

	Vector3 operator*(const Quaternion& q, const Vector3& v);

	std::ostream& operator<<(std::ostream& stream, const Quaternion& q);
}