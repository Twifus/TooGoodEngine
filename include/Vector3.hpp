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

		static const Vector3 zero;
		static const Vector3 one;
		static const Vector3 right;
		static const Vector3 up;
		static const Vector3 forward;

		Vector3();
		Vector3(double x, double y, double z);

		bool operator==(const Vector3 & other) const;		// Comparison, vectors are equal if they are equal component by component
		bool operator!=(const Vector3 & other) const;		// Comparison like above

		Vector3 operator+(const Vector3 & other) const;		// Addition component by component
		Vector3 operator-(const Vector3 & other) const;		// Subtraction by component
		Vector3 operator*(const Vector3 & other) const;		// Multiplication by component
		Vector3 operator/(const Vector3 & other) const;		// Division by component

		Vector3 operator-() const;							// Opposite vector

		Vector3& operator+=(const Vector3 & other);			// Addition by component
		Vector3& operator-=(const Vector3 & other);			// Subtraction by component
		Vector3& operator*=(const Vector3 & other);			// Multiplication by component
		Vector3& operator/=(const Vector3 & other);			// Division by component

		Vector3& operator*=(double k);						// Multiplication vector by scalar
		Vector3& operator/=(double k);						// Division of a vector by a scalar

		static double Dot(const Vector3 & lhs, const Vector3 & rhs);	// Scalar product of two vectors
		static Vector3 Cross(const Vector3 & lhs, const Vector3 & rhs);	// Mathematical cross product

		Vector3 Normalized() const;							// Returns the vector of same direction and of norm 1
		double Magnitude() const;							// Returns the norm of the vector
		double SquaredMagnitude() const;					// Returns the square of the norm of the vector
	};

	Vector3 operator*(const Vector3 & v, double k);			// Multiplication by scalar
	Vector3 operator*(double k, const Vector3 & v);			// Symmetrical of the multiplication by a scalar
	Vector3 operator/(const Vector3 & v, double k);			// Division by a scalar

	std::ostream& operator<<(std::ostream & stream, const Vector3 & v);	// Console display of a vector
}