#include "Quaternion.hpp"

#include <cmath>

namespace TooGoodEngine
{
	const Quaternion Quaternion::identity(1, 0, 0, 0);

	Quaternion::Quaternion() : w(0), x(0), y(0), z(0) {}

	Quaternion::Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}

	Quaternion Quaternion::AxisAngle(const Vector3& axis, double angle)
	{
		Vector3 n = axis.Normalized();
		double theta = angle / 2;
		return Quaternion(std::cos(theta), std::sin(theta) * n.x, std::sin(theta) * n.y, std::sin(theta) * n.z);
	}

	bool Quaternion::operator==(const Quaternion& other) const
	{
		return w == other.w && x == other.x && y == other.y && z == other.z;
	}

	bool Quaternion::operator!=(const Quaternion& other) const
	{
		return !((*this) == other);
	}

	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-w, -x, -y, -z);
	}

	Quaternion Quaternion::operator+() const
	{
		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		Quaternion result;
		result.w = w * other.w - x * other.x - y * other.y - z * other.z;
		result.x = w * other.x + x * other.w + y * other.z - z * other.y;
		result.y = w * other.y + y * other.w + z * other.x - x * other.z;
		result.z = w * other.z + z * other.w + x * other.y - y * other.x;
		return result;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& other)
	{
		(*this) = (*this) * other;
		return *this;
	}

	double Quaternion::Dot(const Quaternion& other) const
	{
		return w * other.w + x * other.x + y * other.y + z * other.z;
	}

	Quaternion Quaternion::Normalized() const
	{
		return Quaternion(w, x, y, z) / Magnitude();
	}

	double Quaternion::Magnitude() const
	{
		return std::sqrt(SquaredMagnitude());
	}

	double Quaternion::SquaredMagnitude() const
	{
		return w * w + x * x + y * y + z * z;
	}

	Quaternion Quaternion::Inverted() const
	{
		return Quaternion(w, -x, -y, -z) / SquaredMagnitude();
	}

	Quaternion operator*(const Quaternion& q, double k)
	{
		return Quaternion(q.w * k, q.x * k, q.y * k, q.z * k);
	}

	Quaternion operator*(double k, const Quaternion& q)
	{
		return q * k;
	}

	Quaternion operator/(const Quaternion& q, double k)
	{
		return Quaternion(q.w / k, q.x / k, q.y / k, q.z / k);
	}

	Quaternion& operator*=(Quaternion& q, double k)
	{
		return (q = q * k);
	}

	Quaternion& operator/=(Quaternion& q, double k)
	{
		return (q = q / k);
	}

	Vector3 operator*(const Quaternion& q, const Vector3& v)
	{
		Quaternion p(0, v.x, v.y, v.z);
		Quaternion result = q * p * q.Inverted();
		return Vector3(result.x, result.y, result.z);
	}

	std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
	{
		return stream << "(w : " << q.w << ", x : " << q.x << ", y : " << q.y << ", z : " << q.z << ")";
	}

}