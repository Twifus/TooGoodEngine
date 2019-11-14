#include "Matrix4.hpp"

namespace TooGoodEngine {
	Matrix4::Matrix4() : m_data() {}

	Matrix4::Matrix4(std::array<double, Matrix4::data_length> matrix) : m_data(matrix) {}

	Matrix4::Matrix4(double matrix[data_length]) : m_data() {
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

	Matrix4 Matrix4::operator+(const Matrix4& matrix) const {
		Matrix4 result;
		for (int i = 0; i < data_length; i++) {
			result[i] = m_data[i] + matrix[i];
		}
		return result;
	}

	Vector3 Matrix4::operator*(const Vector3& vector) const {
		return Vector3(
			m_data[0] * vector.x + m_data[1] * vector.y + m_data[2] * vector.z,
			m_data[4] * vector.x + m_data[5] * vector.y + m_data[6] * vector.z,
			m_data[8] * vector.x + m_data[9] * vector.y + m_data[10] * vector.z
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

	double Matrix4::operator[](const int index) const {
		return m_data[index];
	}

	double& Matrix4::operator[](const int index) {
		return m_data[index];
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

	Matrix4& Matrix4::operator+=(const Matrix4& matrix) {
		for (int i = 0; i < data_length; i++) (*this)[i] += matrix[i];
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& matrix) {
		return ((*this) = (*this) * matrix);
	}

	Matrix4& Matrix4::operator*=(const double k) {
		for (int i = 0; i < data_length; i++) (*this)[i] *= k;
		return *this;
	}

	Matrix4& Matrix4::operator/=(const double k) {
		for (int i = 0; i < data_length; i++) (*this)[i] /= k;
		return *this;
	}

	double Matrix4::ComputeDet() const {
		return (
			(*this)[8] * (*this)[5] * (*this)[2] +
			(*this)[4] * (*this)[9] * (*this)[2] +
			(*this)[8] * (*this)[1] * (*this)[6] -
			(*this)[0] * (*this)[9] * (*this)[6] -
			(*this)[4] * (*this)[1] * (*this)[10] -
			(*this)[0] * (*this)[5] * (*this)[10]
			);
	}

	bool Matrix4::IsInvertible() const {
		return (ComputeDet() != 0);
	}

	Matrix4 Matrix4::Inverse() const {
		double det = ComputeDet();

		// Compute values at index 3, 7 and 11
		double index3 = (
			(*this)[9] * (*this)[6] * (*this)[3] +
			(*this)[1] * (*this)[10] * (*this)[7] +
			(*this)[5] * (*this)[2] * (*this)[11] -
			(*this)[5] * (*this)[10] * (*this)[3] -
			(*this)[9] * (*this)[2] * (*this)[7] -
			(*this)[1] * (*this)[6] * (*this)[11]) / det;

		double index7 = (
			(*this)[4] * (*this)[10] * (*this)[3] +
			(*this)[8] * (*this)[2] * (*this)[7] +
			(*this)[0] * (*this)[6] * (*this)[11] -
			(*this)[8] * (*this)[6] * (*this)[3] -
			(*this)[0] * (*this)[10] * (*this)[7] -
			(*this)[4] * (*this)[2] * (*this)[11]) / det;

		double index11 = (
			(*this)[8] * (*this)[5] * (*this)[3] +
			(*this)[0] * (*this)[9] * (*this)[7] +
			(*this)[4] * (*this)[1] * (*this)[11] -
			(*this)[0] * (*this)[5] * (*this)[11] -
			(*this)[4] * (*this)[9] * (*this)[3] -
			(*this)[8] * (*this)[1] * (*this)[7]) / det;

		// Creates an array of the component of the inverse matrix
		return Matrix4({ 
			((*this)[5] * (*this)[10] - (*this)[9] * (*this)[6]) / det,
			((*this)[2] * (*this)[9] - (*this)[1] * (*this)[10]) / det,
			((*this)[1] * (*this)[6] - (*this)[2] * (*this)[5]) / det,
			index3,
			((*this)[8] * (*this)[6] - (*this)[4] * (*this)[10]) / det,
			((*this)[0] * (*this)[10] - (*this)[2] * (*this)[8]) / det,
			((*this)[2] * (*this)[4] - (*this)[0] * (*this)[6]) / det,
			index7,
			((*this)[4] * (*this)[9] - (*this)[5] * (*this)[8]) / det,
			((*this)[1] * (*this)[8] - (*this)[0] * (*this)[9]) / det,
			((*this)[0] * (*this)[5] - (*this)[1] * (*this)[4]) / det,
			index11 
			});
	}

	Matrix4 Matrix4::Transpose() const {
		Matrix4 transpose;
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size; j++) {
				transpose[i * size + j] = m_data[static_cast<uint64_t>(j) * size + i];
			}
		}
		return transpose;
	}
}