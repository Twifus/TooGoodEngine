#pragma once

#include <ostream>

namespace TooGoodEngine
{
	class Vector3
	{
	public:
		double x;
		double y;
		double z;

		Vector3();
		Vector3(double x, double y, double z);

		bool operator==(const Vector3 & other) const;
		bool operator!=(const Vector3 & other) const;

		Vector3 operator+(const Vector3 & other) const;
		Vector3 operator-(const Vector3 & other) const;
		Vector3 operator*(const Vector3 & other) const;
		Vector3 operator/(const Vector3 & other) const;

		Vector3 operator-() const;

		Vector3& operator+=(const Vector3 & other);
		Vector3& operator-=(const Vector3 & other);
		Vector3& operator*=(const Vector3 & other);
		Vector3& operator/=(const Vector3 & other);

		Vector3& operator*=(double k);
		Vector3& operator/=(double k);

		double operator[](int index) const;
		double& operator[](int index);

		static double Dot(const Vector3 & lhs, const Vector3 & rhs);
		static Vector3 Cross(const Vector3 & lhs, const Vector3 & rhs);

		Vector3 Normalize() const;
		double Magnitude() const;
		double SquaredMagnitude() const;
	};

	Vector3 operator*(const Vector3 & v, double k);
	Vector3 operator*(double k, const Vector3 & v);
	Vector3 operator/(const Vector3 & v, double k);

	std::ostream& operator<<(std::ostream & stream, const Vector3 & v);
}