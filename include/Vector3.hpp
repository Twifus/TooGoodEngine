#pragma once

#include <ostream>

namespace TooGoodEngine
{
	/**
	 * Represents a vector in a 3D space
	 */
	class Vector3
	{
	public:
		double x, y, z;

		static const Vector3 zero;		// Vector (0, 0, 0)
		static const Vector3 one;		// Vector (1, 1, 1)
		static const Vector3 right;		// Vector pointing right
		static const Vector3 up;		// Vector pointing up
		static const Vector3 forward;	// Vector pointing forward

		Vector3();								// Construct a vector of coordinates (0, 0, 0)
		Vector3(double x, double y, double z);	// Construct a vector of coordinates (x, y, z)

		bool operator==(const Vector3& other) const;		// Comparison, vectors are equal if they are equal component by component
		bool operator!=(const Vector3& other) const;		// Comparison, vectors are different if at least one of their components is different

		Vector3 operator-() const;							// Opposite vector
		Vector3 operator+() const;							// Vector (just for completeness)

		Vector3 operator+(const Vector3& other) const;		// Addition component by component
		Vector3 operator-(const Vector3& other) const;		// Subtraction component by component
		Vector3 operator*(const Vector3& other) const;		// Multiplication component by component
		Vector3 operator/(const Vector3& other) const;		// Division component by component

		Vector3& operator+=(const Vector3& other);			// Addition component by component
		Vector3& operator-=(const Vector3& other);			// Subtraction component by component
		Vector3& operator*=(const Vector3& other);			// Multiplication component by component
		Vector3& operator/=(const Vector3& other);			// Division component by component

		double Dot(const Vector3& other) const;				// Scalar product of two vectors
		Vector3 Cross(const Vector3& other) const;			// Mathematical cross product

		Vector3 Normalized() const;							// Returns the vector of same direction and of norm 1
		double Magnitude() const;							// Returns the norm of the vector
		double SquaredMagnitude() const;					// Returns the square of the norm of the vector
	};

	Vector3 operator*(const Vector3& v, double k);			// Multiplication of each component by a scalar
	Vector3 operator*(double k, const Vector3& v);			// Multiplication of each component by a scalar
	Vector3 operator/(const Vector3& v, double k);			// Division of each component by a scalar

	Vector3& operator*=(Vector3& v, double k);				// Multiplication of each component by a scalar
	Vector3& operator/=(Vector3& v, double k);				// Division of each component by a scalar

	std::ostream& operator<<(std::ostream& stream, const Vector3& v);	// Console display of a vector
}