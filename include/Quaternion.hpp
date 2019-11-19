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
		Quaternion(const Vector3& v);

		static Quaternion AxisAngle(const Vector3& axis, double angle);

		bool operator==(const Quaternion& other) const;
		bool operator!=(const Quaternion& other) const;

		Quaternion operator-() const;
		Quaternion operator+() const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;

		Quaternion& operator+=(const Quaternion& other);
		Quaternion& operator-=(const Quaternion& other);
		Quaternion& operator*=(const Quaternion& other);
		
		static Quaternion Log(const Quaternion& q);
		static Quaternion Exp(const Quaternion& q);
		Quaternion Pow(double e) const;
		Quaternion Pow(const Quaternion& q) const;

		double Dot(const Quaternion& other) const;

		static double Angle(const Quaternion& from, const Quaternion& to);
		static Quaternion Delta(const Quaternion& from, const Quaternion& to);

		Quaternion Normalized() const;
		double Magnitude() const;
		double SquaredMagnitude() const;

		Quaternion Conjugate() const;
		Quaternion Inverse() const;
	};

	Quaternion operator*(const Quaternion& q, double k);
	Quaternion operator*(double k, const Quaternion& q);
	Quaternion operator/(const Quaternion& q, double k);

	Quaternion& operator*=(Quaternion& q, double k);
	Quaternion& operator/=(Quaternion& q, double k);

	Vector3 operator*(const Quaternion& q, const Vector3& v);

	std::ostream& operator<<(std::ostream& stream, const Quaternion& q);
}