#include "Matrix4.hpp"

namespace TooGoodEngine
{
	const Matrix4 Matrix4::identity({ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 });
	
	Matrix4::Matrix4() : m_data() {}

	Matrix4::Matrix4(const std::array<double, Matrix4::data_length> matrix) : m_data(matrix) {}

	Matrix4::Matrix4(const double matrix[Matrix4::data_length]) : m_data() {
		for (int i = 0; i < data_length; i++) m_data[i] = matrix[i];
	}

	Matrix4::Matrix4(const Vector3& vector) : m_data() {
		m_data[3] = vector.x;
		m_data[7] = vector.y;
		m_data[11] = vector.z;
	}

	Matrix4::Matrix4(const Matrix3& m, const Vector3& v) : Matrix4(v) {
		for (int i = 0; i < Matrix3::size; i++) {
			for (int j = 0; j < Matrix3::size; j++) {
				m_data[static_cast<uint64_t>(i)* size + j] = m[i * Matrix3::size + j]; // the cast prevents overflows (may be overkill here)
			}
		}
	}

	Matrix4::Matrix4(const Quaternion& q, const Vector3& v) : Matrix4(Matrix3(q), v) {}

	const std::array<double, Matrix4::data_length> Matrix4::data() const
	{
		return m_data;
	}

	bool Matrix4::operator==(const Matrix4& matrix) const {
		for (int i = 0; i < data_length; i++) {
			if (m_data[i] != matrix[i]) return false;
		}
		return true;
	}

	bool Matrix4::operator!=(const Matrix4& matrix) const {
		return !((*this) == matrix);
	}

	double Matrix4::operator[](const int index) const {
		return m_data[index];
	}

	double& Matrix4::operator[](const int index) {
		return m_data[index];
	}

	Matrix4 Matrix4::operator+(const Matrix4& matrix) const {
		Matrix4 result;
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] + matrix[i];
		}
		return result;
	}

	Matrix4 Matrix4::operator-(const Matrix4& matrix) const {
		Matrix4 result;
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] - matrix[i];
		}
		return result;
	}

	Vector3 Matrix4::operator*(const Vector3& vector) const {
		return Vector3(
			m_data[0] * vector.x + m_data[1] * vector.y + m_data[2] * vector.z + m_data[3],
			m_data[4] * vector.x + m_data[5] * vector.y + m_data[6] * vector.z + m_data[7],
			m_data[8] * vector.x + m_data[9] * vector.y + m_data[10] * vector.z + m_data[11]
		);
	}

	Matrix4 Matrix4::operator*(const Matrix4& matrix) const {
		return Matrix4({
			m_data[0] * matrix[0] + m_data[1] * matrix[4] + m_data[2] * matrix[8],
			m_data[0] * matrix[1] + m_data[1] * matrix[5] + m_data[2] * matrix[9],
			m_data[0] * matrix[2] + m_data[1] * matrix[6] + m_data[2] * matrix[10],
			m_data[0] * matrix[3] + m_data[1] * matrix[7] + m_data[2] * matrix[11] + m_data[3],
			m_data[4] * matrix[0] + m_data[5] * matrix[4] + m_data[6] * matrix[8],
			m_data[4] * matrix[1] + m_data[5] * matrix[5] + m_data[6] * matrix[9],
			m_data[4] * matrix[2] + m_data[5] * matrix[6] + m_data[6] * matrix[10],
			m_data[4] * matrix[3] + m_data[5] * matrix[7] + m_data[6] * matrix[11] + m_data[7],
			m_data[8] * matrix[0] + m_data[9] * matrix[4] + m_data[10] * matrix[8],
			m_data[8] * matrix[1] + m_data[9] * matrix[5] + m_data[10] * matrix[9],
			m_data[8] * matrix[2] + m_data[9] * matrix[6] + m_data[10] * matrix[10],
			m_data[8] * matrix[3] + m_data[9] * matrix[7] + m_data[10] * matrix[11] + m_data[11]
			});
	}

	Matrix4 Matrix4::operator*(const double k) const {
		Matrix4 result;
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] * k;
		}
		return result;
	}

	Matrix4 Matrix4::operator/(const double k) const {
		Matrix4 result;
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] / k;
		}
		return result;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& matrix) {
		for (int i = 0; i < data_length; i++) m_data[i] += matrix[i];
		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& matrix) {
		for (int i = 0; i < data_length; i++) m_data[i] -= matrix[i];
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& matrix) {
		return ((*this) = (*this) * matrix);
	}

	Matrix4& Matrix4::operator*=(const double k) {
		for (int i = 0; i < data_length; i++) m_data[i] *= k;
		return *this;
	}

	Matrix4& Matrix4::operator/=(const double k) {
		for (int i = 0; i < data_length; i++) m_data[i] /= k;
		return *this;
	}

	double Matrix4::ComputeDet() const {
		return (
			m_data[0] * m_data[5] * m_data[10]
			+ m_data[2] * m_data[4] * m_data[9]
			+ m_data[1] * m_data[6] * m_data[8]
			- m_data[0] * m_data[6] * m_data[9]
			- m_data[2] * m_data[5] * m_data[8]
			- m_data[1] * m_data[4] * m_data[10]
			);
	}

	bool Matrix4::IsInvertible() const {
		return (ComputeDet() != 0);
	}

	Matrix4 Matrix4::Inverse() const {
		double det = ComputeDet();

		// Compute values at index 3, 7 and 11
		double index3 = (
			m_data[9] * m_data[6] * m_data[3] +
			m_data[1] * m_data[10] * m_data[7] +
			m_data[5] * m_data[2] * m_data[11] -
			m_data[5] * m_data[10] * m_data[3] -
			m_data[9] * m_data[2] * m_data[7] -
			m_data[1] * m_data[6] * m_data[11]) / det;

		double index7 = (
			m_data[4] * m_data[10] * m_data[3] +
			m_data[8] * m_data[2] * m_data[7] +
			m_data[0] * m_data[6] * m_data[11] -
			m_data[8] * m_data[6] * m_data[3] -
			m_data[0] * m_data[10] * m_data[7] -
			m_data[4] * m_data[2] * m_data[11]) / det;

		double index11 = (
			m_data[8] * m_data[5] * m_data[3] +
			m_data[0] * m_data[9] * m_data[7] +
			m_data[4] * m_data[1] * m_data[11] -
			m_data[0] * m_data[5] * m_data[11] -
			m_data[4] * m_data[9] * m_data[3] -
			m_data[8] * m_data[1] * m_data[7]) / det;

		// Creates an array of the component of the inverse matrix
		return Matrix4({
			(m_data[5] * m_data[10] - m_data[9] * m_data[6]) / det,
			(m_data[2] * m_data[9] - m_data[1] * m_data[10]) / det,
			(m_data[1] * m_data[6] - m_data[2] * m_data[5]) / det,
			index3,
			(m_data[8] * m_data[6] - m_data[4] * m_data[10]) / det,
			(m_data[0] * m_data[10] - m_data[2] * m_data[8]) / det,
			(m_data[2] * m_data[4] - m_data[0] * m_data[6]) / det,
			index7,
			(m_data[4] * m_data[9] - m_data[5] * m_data[8]) / det,
			(m_data[1] * m_data[8] - m_data[0] * m_data[9]) / det,
			(m_data[0] * m_data[5] - m_data[1] * m_data[4]) / det,
			index11
			});
	}

	Matrix4 Matrix4::Transpose() const {
		Matrix4 transpose;
		for (int i = 0; i < Matrix3::size; i++) {
			for (int j = 0; j < Matrix3::size; j++) {
				transpose[i * Matrix4::size + j] = m_data[static_cast<uint64_t>(j)* Matrix4::size + i];
			}
		}
		transpose[3] = -m_data[3];
		transpose[7] = -m_data[7];
		transpose[11] = -m_data[11];
		return transpose;
	}
}