#include "Vector3.hpp"

#include <cmath>
#include <ostream>
#include <stdexcept>

namespace TooGoodEngine
{
	Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

	bool Vector3::operator==(const Vector3 & other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3::operator!=(const Vector3 & other) const
	{
		return !(*this == other);
	}

	Vector3 Vector3::operator+(const Vector3 & other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 Vector3::operator-(const Vector3 & other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 Vector3::operator*(const Vector3 & other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3 Vector3::operator/(const Vector3 & other) const
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 & Vector3::operator+=(const Vector3 & other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3 & Vector3::operator-=(const Vector3 & other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3 & Vector3::operator*=(const Vector3 & other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3 & Vector3::operator/=(const Vector3 & other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vector3 & Vector3::operator*=(double k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	Vector3 & Vector3::operator/=(double k)
	{
		x /= k;
		y /= k;
		z /= k;
		return *this;
	}

	double Vector3::operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::out_of_range("Vector3 contains only 3 elements");
		}
	}

	double& Vector3::operator[](int index)
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::out_of_range("Vector3 contains only 3 elements");
		}
	}

	double Vector3::Dot(const Vector3 &lhs, const Vector3 &rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	Vector3 Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs)
	{
		return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
	}

	Vector3 Vector3::Normalize() const
	{
		double magnitude = Magnitude();
		return *this / magnitude;
	}

	double Vector3::Magnitude() const
	{
		return std::sqrt(SquaredMagnitude());
	}

	double Vector3::SquaredMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	Vector3 operator*(double k, const Vector3 & v)
	{
		return Vector3(k * v.x, k * v.y, k * v.z);
	}

	Vector3 operator*(const Vector3 & v, double k)
	{
		return k * v;
	}

	Vector3 operator/(const Vector3 & v, double k)
	{
		return Vector3(v.x / k, v.y / k, v.z / k);
	}

	std::ostream & operator<<(std::ostream & out, const Vector3 & v)
	{
		return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
}