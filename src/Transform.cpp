#include "Transform.hpp"

namespace TooGoodEngine
{
	const Transform Transform::identity({ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 });
	
	Transform::Transform() : m_data() {}

	Transform::Transform(const std::array<double, Transform::data_length> matrix) : m_data(matrix) {}

	Transform::Transform(const double matrix[Transform::data_length]) : m_data() {
		for (int i = 0; i < data_length; i++) m_data[i] = matrix[i];
	}

	Transform::Transform(const Vector3& vector) : m_data() {
		m_data[3] = vector.x;
		m_data[7] = vector.y;
		m_data[11] = vector.z;
	}

	Transform::Transform(const Matrix3& m, const Vector3& v) : Transform(v) {
		for (int i = 0; i < Matrix3::size; i++) {
			for (int j = 0; j < Matrix3::size; j++) {
				m_data[static_cast<uint64_t>(i)* size + j] = m[i * Matrix3::size + j]; // the cast prevents overflows (may be overkill here)
			}
		}
	}

	Transform::Transform(const Quaternion& q, const Vector3& v) : Transform(Matrix3(q), v) {}

	const std::array<double, Transform::data_length> Transform::data() const
	{
		return m_data;
	}

	bool Transform::operator==(const Transform& matrix) const {
		for (int i = 0; i < data_length; i++) {
			if (m_data[i] != matrix[i]) return false;
		}
		return true;
	}

	bool Transform::operator!=(const Transform& matrix) const {
		return !((*this) == matrix);
	}

	double Transform::operator[](const int index) const {
		return m_data[index];
	}

	double& Transform::operator[](const int index) {
		return m_data[index];
	}

	Vector3 Transform::operator*(const Vector3& vector) const {
		return Vector3(
			m_data[0] * vector.x + m_data[1] * vector.y + m_data[2] * vector.z + m_data[3],
			m_data[4] * vector.x + m_data[5] * vector.y + m_data[6] * vector.z + m_data[7],
			m_data[8] * vector.x + m_data[9] * vector.y + m_data[10] * vector.z + m_data[11]
		);
	}

	Transform Transform::operator*(const Transform& matrix) const {
		return Transform({
			m_data[0] * matrix[0] + m_data[1] * matrix[4] + m_data[2] * matrix[8],
			m_data[0] * matrix[1] + m_data[1] * matrix[5] + m_data[2] * matrix[9],
			m_data[0] * matrix[2] + m_data[1] * matrix[6] + m_data[2] * matrix[10],
			m_data[3] + matrix[3],
			m_data[4] * matrix[0] + m_data[5] * matrix[4] + m_data[6] * matrix[8],
			m_data[4] * matrix[1] + m_data[5] * matrix[5] + m_data[6] * matrix[9],
			m_data[4] * matrix[2] + m_data[5] * matrix[6] + m_data[6] * matrix[10],
			m_data[7] + matrix[7],
			m_data[8] * matrix[0] + m_data[9] * matrix[4] + m_data[10] * matrix[8],
			m_data[8] * matrix[1] + m_data[9] * matrix[5] + m_data[10] * matrix[9],
			m_data[8] * matrix[2] + m_data[9] * matrix[6] + m_data[10] * matrix[10],
			m_data[11] + matrix[11]
			});
	}

	Transform& Transform::operator*=(const Transform& matrix) {
		return ((*this) = (*this) * matrix);
	}

	double Transform::ComputeDet() const {
		return (
			m_data[0] * m_data[5] * m_data[10]
			+ m_data[2] * m_data[4] * m_data[9]
			+ m_data[1] * m_data[6] * m_data[8]
			- m_data[0] * m_data[6] * m_data[9]
			- m_data[2] * m_data[5] * m_data[8]
			- m_data[1] * m_data[4] * m_data[10]
			);
	}

	bool Transform::IsInvertible() const {
		return (ComputeDet() != 0);
	}

	Transform Transform::Inverse() const {
		double det = ComputeDet();

		// Creates an array of the component of the inverse matrix
		return Transform({
			(m_data[5] * m_data[10] - m_data[9] * m_data[6]) / det,
			(m_data[2] * m_data[9] - m_data[1] * m_data[10]) / det,
			(m_data[1] * m_data[6] - m_data[2] * m_data[5]) / det,
			-m_data[3],
			(m_data[8] * m_data[6] - m_data[4] * m_data[10]) / det,
			(m_data[0] * m_data[10] - m_data[2] * m_data[8]) / det,
			(m_data[2] * m_data[4] - m_data[0] * m_data[6]) / det,
			-m_data[7],
			(m_data[4] * m_data[9] - m_data[5] * m_data[8]) / det,
			(m_data[1] * m_data[8] - m_data[0] * m_data[9]) / det,
			(m_data[0] * m_data[5] - m_data[1] * m_data[4]) / det,
			-m_data[11]
			});
	}
}