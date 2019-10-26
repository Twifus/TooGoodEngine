#include "Vector3.hpp"

#include <cmath>

namespace TooGoodEngine
{
	const Vector3 Vector3::zero(0, 0, 0);
	const Vector3 Vector3::one(1, 1, 1);
	const Vector3 Vector3::right(1, 0, 0);
	const Vector3 Vector3::up(0, 1, 0);
	const Vector3 Vector3::forward(0, 0, 1);

	Vector3::Vector3() : x(0), y(0), z(0) {}

	Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

	bool Vector3::operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3::operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 Vector3::operator+() const
	{
		return *this;
	}

	Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3 Vector3::operator/(const Vector3& other) const
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	Vector3& Vector3::operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	double Vector3::Dot(const Vector3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	Vector3 Vector3::Cross(const Vector3& other) const
	{
		return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	Vector3 Vector3::Normalized() const
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

	Vector3 operator*(double k, const Vector3& v)
	{
		return Vector3(k * v.x, k * v.y, k * v.z);
	}

	Vector3 operator*(const Vector3& v, double k)
	{
		return k * v;
	}

	Vector3 operator/(const Vector3& v, double k)
	{
		return Vector3(v.x / k, v.y / k, v.z / k);
	}

	Vector3& operator*=(Vector3& v, double k)
	{
		return (v = v * k);
	}

	Vector3& operator/=(Vector3& v, double k)
	{
		return (v = v * k);
	}

	std::ostream& operator<<(std::ostream& out, const Vector3& v)
	{
		return out << "(x : " << v.x << ", y : " << v.y << ", z : " << v.z << ")";
	}
}