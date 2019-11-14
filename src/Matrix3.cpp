#include "Matrix3.hpp"

namespace TooGoodEngine
{
	const Matrix3 Matrix3::identity({ 1, 0, 0, 0, 1, 0, 0, 0, 1 });

	Matrix3::Matrix3() : m_data() {}

	Matrix3::Matrix3(const std::array<double, Matrix3::data_length> matrix) : m_data(matrix) {}

	Matrix3::Matrix3(const double matrix[Matrix3::data_length]) : m_data() {
		for (int i = 0; i < data_length; i++) m_data[i] = matrix[i];
	}

	Matrix3::Matrix3(const Quaternion& q) {
		m_data = {
			1 - (2 * q.y * q.y + 2 * q.z * q.z),
			2 * q.x * q.y + 2 * q.z * q.w,
			2 * q.x * q.z - 2 * q.y * q.w,
			2 * q.x * q.y - 2 * q.z * q.w,
			1 - (2 * q.x * q.x + 2 * q.z * q.z),
			2 * q.y * q.z + 2 * q.x * q.w,
			2 * q.x * q.z + 2 * q.y * q.w,
			2 * q.y * q.z - 2 * q.x * q.w,
			1 - (2 * q.x * q.x + 2 * q.y * q.y)
		};
	}

	Matrix3::Matrix3(const Vector3& vector) : m_data() {
		m_data[0] = vector.x;
		m_data[4] = vector.y;
		m_data[8] = vector.z;
	}

	const std::array<double, Matrix3::data_length> Matrix3::data() const
	{
		return m_data;
	}

	bool Matrix3::operator==(const Matrix3& matrix) const {
		return m_data == matrix.m_data;
	}

	bool Matrix3::operator!=(const Matrix3& matrix) const {
		return !(*this == matrix);
	}

	double Matrix3::operator[](const int index) const {
		return m_data[index];
	}

	double& Matrix3::operator[](const int index) {
		return m_data[index];
	}

	Matrix3 Matrix3::operator+(const Matrix3& matrix) const {
		Matrix3 result;
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] + matrix[i];
		}
		return result;
	}

	Matrix3 Matrix3::operator-(const Matrix3& matrix) const
	{
		Matrix3 result;
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] - matrix[i];
		}
		return result;
	}

	Vector3 Matrix3::operator*(const Vector3& vector) const {
		return Vector3(
			m_data[0] * vector.x + m_data[1] * vector.y + m_data[2] * vector.z,
			m_data[3] * vector.x + m_data[4] * vector.y + m_data[5] * vector.z,
			m_data[6] * vector.x + m_data[7] * vector.y + m_data[8] * vector.z
		);
	}

	Matrix3 Matrix3::operator*(const Matrix3& matrix) const {
		double tmp[data_length] = { 
			m_data[0] * matrix[0] + m_data[1] * matrix[3] + m_data[2] * matrix[6],
			m_data[0] * matrix[1] + m_data[1] * matrix[4] + m_data[2] * matrix[7],
			m_data[0] * matrix[2] + m_data[1] * matrix[5] + m_data[2] * matrix[8],
			m_data[3] * matrix[0] + m_data[4] * matrix[3] + m_data[5] * matrix[6],
			m_data[3] * matrix[1] + m_data[4] * matrix[4] + m_data[5] * matrix[7],
			m_data[3] * matrix[2] + m_data[4] * matrix[5] + m_data[5] * matrix[8],
			m_data[6] * matrix[0] + m_data[7] * matrix[3] + m_data[8] * matrix[6],
			m_data[6] * matrix[1] + m_data[7] * matrix[4] + m_data[8] * matrix[7],
			m_data[6] * matrix[2] + m_data[7] * matrix[5] + m_data[8] * matrix[8]
		};

		return Matrix3(tmp);
	}

	Matrix3 Matrix3::operator*(const double k) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] * k;
		}
		return result;
	}

	Matrix3 Matrix3::operator/(const double k) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] / k;
		}
		return result;
	}

	Matrix3& Matrix3::operator+=(const Matrix3& matrix) {
		for (int i = 0; i < data_length; i++) m_data[i] += matrix[i];
		return *this;
	}

	Matrix3& Matrix3::operator-=(const Matrix3& matrix) {
		for (int i = 0; i < data_length; i++) m_data[i] -= matrix[i];
		return *this;
	}

	Matrix3& Matrix3::operator*=(const Matrix3& matrix) {
		return ((*this) = (*this) * matrix);
	}

	Matrix3& Matrix3::operator*=(const double k) {
		for (int i = 0; i < data_length; i++) m_data[i] *= k;
		return *this;
	}

	Matrix3& Matrix3::operator/=(const double k) {
		for (int i = 0; i < data_length; i++) m_data[i] /= k;
		return *this;
	}

	double Matrix3::ComputeDet() const {
		return (
			m_data[0] * m_data[4] * m_data[8] +
			m_data[3] * m_data[7] * m_data[2] +
			m_data[6] * m_data[1] * m_data[5] -
			m_data[0] * m_data[7] * m_data[5] -
			m_data[6] * m_data[4] * m_data[2] -
			m_data[3] * m_data[1] * m_data[8]
			);
	}

	bool Matrix3::IsInvertible() const {
		return (ComputeDet() != 0);
	}

	Matrix3 Matrix3::Inverse() const {
		double det = ComputeDet();

		return Matrix3 ({
			(m_data[4] * m_data[8] - m_data[5] * m_data[7]) / det,
			(m_data[2] * m_data[7] - m_data[1] * m_data[8]) / det,
			(m_data[1] * m_data[5] - m_data[2] * m_data[4]) / det,
			(m_data[5] * m_data[6] - m_data[3] * m_data[8]) / det,
			(m_data[0] * m_data[8] - m_data[2] * m_data[6]) / det,
			(m_data[2] * m_data[3] - m_data[0] * m_data[5]) / det,
			(m_data[3] * m_data[7] - m_data[4] * m_data[6]) / det,
			(m_data[1] * m_data[6] - m_data[0] * m_data[7]) / det,
			(m_data[0] * m_data[4] - m_data[1] * m_data[3]) / det 
		});
	}

	Matrix3 Matrix3::Transpose() const {
		Matrix3 transpose = Matrix3();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				transpose[i * size + j] = m_data[static_cast<uint64_t>(j) * size + i];
			}
		}
		return transpose;
	}

	void Matrix3::SetOrientation(Quaternion& q) {
		*this = Matrix3(q);
	}

	Matrix3 Matrix3::BaseChange(Vector3& base) {
		Matrix3 baseMatrix(base);
		return baseMatrix * (*this) * baseMatrix.Inverse();
	}
}