#include "Vector3.hpp"

#include <cmath>

namespace TooGoodEngine
{
	const Vector3 Vector3::zero(0, 0, 0);		// Vector (0, 0, 0)
	const Vector3 Vector3::one(1, 1, 1);		// Vector (1, 1, 1)
	const Vector3 Vector3::right(1, 0, 0);		// Vector pointing right
	const Vector3 Vector3::up(0, 1, 0);			// Vector pointing up
	const Vector3 Vector3::forward(0, 0, 1);	// Vector pointing forward

	// Construct a vector of coordinates (0, 0, 0)
	Vector3::Vector3() : x(0), y(0), z(0) {}

	// Construct a vector of coordinates (x, y, z)
	Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

	// Comparison, vectors are equal if they are equal component by component
	bool Vector3::operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	// Comparison, vectors are different if at least one of their components is different
	bool Vector3::operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}

	// Opposite vector
	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	// Vector (just for completeness)
	Vector3 Vector3::operator+() const
	{
		return *this;
	}

	// Addition component by component
	Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	// Subtraction component by component
	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	// Multiplication component by component
	Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	// Division component by component
	Vector3 Vector3::operator/(const Vector3& other) const
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	// Addition component by component
	Vector3& Vector3::operator+=(const Vector3& other)
	{
		return (*this = *this + other);
	}

	// Subtraction component by component
	Vector3& Vector3::operator-=(const Vector3& other)
	{
		return (*this = *this - other);
	}

	// Multiplication component by component
	Vector3& Vector3::operator*=(const Vector3& other)
	{
		return (*this = *this * other);
	}

	// Division component by component
	Vector3& Vector3::operator/=(const Vector3& other)
	{
		return (*this = *this / other);
	}

	// Scalar product of two vectors
	double Vector3::Dot(const Vector3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	// Mathematical cross product
	Vector3 Vector3::Cross(const Vector3& other) const
	{
		return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	// Returns the vector of same direction and of norm 1
	Vector3 Vector3::Normalized() const
	{
		double magnitude = Magnitude();
		return *this / magnitude;
	}

	// Returns the norm of the vector
	double Vector3::Magnitude() const
	{
		return std::sqrt(SquaredMagnitude());
	}

	// Returns the square of the norm of the vector
	double Vector3::SquaredMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	// Multiplication of each component by a scalar
	Vector3 operator*(double k, const Vector3& v)
	{
		return Vector3(k * v.x, k * v.y, k * v.z);
	}

	// Multiplication of each component by a scalar
	Vector3 operator*(const Vector3& v, double k)
	{
		return k * v;
	}

	// Division of each component by a scalar
	Vector3 operator/(const Vector3& v, double k)
	{
		return Vector3(v.x / k, v.y / k, v.z / k);
	}

	// Multiplication of each component by a scalar
	Vector3& operator*=(Vector3& v, double k)
	{
		return (v = v * k);
	}

	// Division of each component by a scalar
	Vector3& operator/=(Vector3& v, double k)
	{
		return (v = v * k);
	}

	// Console display of a vector
	std::ostream& operator<<(std::ostream& out, const Vector3& v)
	{
		return out << "(x : " << v.x << ", y : " << v.y << ", z : " << v.z << ")";
	}

	// Bracket accessor
	double Vector3::operator[](int i) const
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;		
		default:
			return 0;
		}
	}
}