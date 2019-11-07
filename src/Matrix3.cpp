#include "Matrix3.hpp"

namespace TooGoodEngine {
	Matrix3::Matrix3() {
		for (int i = 0; i < DATA_LENGTH; i++) data[i] = 0;
	}

	Matrix3::Matrix3(double matrix[DATA_LENGTH]) {
		for (int i = 0; i < DATA_LENGTH; i++) data[i] = matrix[i];
	}
	Matrix3::Matrix3(Vector3 &vector) {
		for (int i = 0; i < DATA_LENGTH; i++) {
			data[i] = 0;
			if (i == 0) data[i] = vector.x;
			if (i == 3) data[i] = vector.y;
			if (i == 6) data[i] = vector.z;
		}
	}
	Matrix3::Matrix3(Quaternion &q) {
		double tmp[DATA_LENGTH] = { 1 - (2 * q.y * q.y + 2 * q.z * q.z),
											2 * q.x * q.y + 2 * q.z * q.w,
											2 * q.x * q.z - 2 * q.y * q.w,
											2 * q.x * q.y - 2 * q.z * q.w,
											1 - (2 * q.x * q.x + 2 * q.z * q.z),
											2 * q.y * q.z + 2 * q.x * q.w,
											2 * q.x * q.z + 2 * q.y * q.w,
											2 * q.y * q.z - 2 * q.x * q.w,
											1 - (2 * q.x * q.x + 2 * q.y * q.y) };

		for (int i = 0; i < DATA_LENGTH; i++) data[i] = tmp[i];
	}

	
	Matrix3 Matrix3::operator+(const Matrix3 &matrix) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < DATA_LENGTH; i++) {
			result[i] = (*this)[i] + matrix[i];
		}
		return result;
	}

	Vector3 Matrix3::operator*(const Vector3 &vector) const {
		return Vector3(	(*this)[0] * vector.x + (*this)[1] * vector.y + (*this)[2] * vector.z,
						(*this)[3] * vector.x + (*this)[4] * vector.y + (*this)[5] * vector.z,
						(*this)[6] * vector.x + (*this)[7] * vector.y + (*this)[8] * vector.z );
	}

	Matrix3 Matrix3::operator*(const Matrix3 &matrix) const {
		double tmp[DATA_LENGTH] = { (*this)[0] * matrix[0] + (*this)[1] * matrix[3] + (*this)[2] * matrix[6],
						(*this)[0] * matrix[1] + (*this)[1] * matrix[4] + (*this)[2] * matrix[7],
						(*this)[0] * matrix[2] + (*this)[1] * matrix[5] + (*this)[2] * matrix[8],
						(*this)[3] * matrix[0] + (*this)[4] * matrix[3] + (*this)[5] * matrix[6],
						(*this)[3] * matrix[1] + (*this)[4] * matrix[4] + (*this)[5] * matrix[7],
						(*this)[3] * matrix[2] + (*this)[4] * matrix[5] + (*this)[5] * matrix[8],
						(*this)[6] * matrix[0] + (*this)[7] * matrix[3] + (*this)[8] * matrix[6],
						(*this)[6] * matrix[1] + (*this)[7] * matrix[4] + (*this)[8] * matrix[7],
						(*this)[6] * matrix[2] + (*this)[7] * matrix[5] + (*this)[8] * matrix[8] };

		return Matrix3(tmp);
	}

	Matrix3 Matrix3::operator*(const double k) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < DATA_LENGTH; i++) {
			result[i] = (*this)[i] * k;
		}
		return result;
	}

	Matrix3 Matrix3::operator/(const double k) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < DATA_LENGTH; i++) {
			result[i] = (*this)[i] / k;
		}
		return result;
	}

	double Matrix3::operator[](const int index) const {
		return this->data[index];
	}

	double& Matrix3::operator[](const int index) {
		return this->data[index];
	}

	bool Matrix3::operator==(const Matrix3 &matrix) const {
		for (int i = 0; i < DATA_LENGTH; i++) {
			if ((*this)[i] != matrix[i]) return false;
		}
		return true;
	}

	bool Matrix3::operator!=(const Matrix3 &matrix) const {
		return !((*this) == matrix);
	}

	Matrix3& Matrix3::operator+=(const Matrix3 &matrix) {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] += matrix[i];
		return *this;
	}

	Matrix3& Matrix3::operator*=(const Matrix3 &matrix) {
		*this = ((*this) * matrix);
		return *this;
	}

	Matrix3& Matrix3::operator*=(const double k) {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] *= k;
		return *this;
	}

	Matrix3& Matrix3::operator/=(const double k) {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] /= k;
		return *this;
	}

	double Matrix3::ComputeDet() const {
		return ((*this)[0] * (*this)[4] * (*this)[8] +
			(*this)[3] * (*this)[7] * (*this)[2] +
			(*this)[6] * (*this)[1] * (*this)[5] -
			(*this)[0] * (*this)[7] * (*this)[5] -
			(*this)[6] * (*this)[4] * (*this)[2] -
			(*this)[3] * (*this)[1] * (*this)[8]);
	}

	bool Matrix3::IsInvertible() const {
		return (this->ComputeDet() != 0);
	}

	Matrix3 Matrix3::Inverse() const {
		double det = this->ComputeDet();

		double tmp[DATA_LENGTH] = { ((*this)[4] * (*this)[8] - (*this)[5] * (*this)[7]) / det,
			((*this)[2] * (*this)[7] - (*this)[1] * (*this)[8]) / det,
			((*this)[1] * (*this)[5] - (*this)[2] * (*this)[4]) / det,
			((*this)[5] * (*this)[6] - (*this)[3] * (*this)[8]) / det,
			((*this)[0] * (*this)[8] - (*this)[2] * (*this)[6]) / det,
			((*this)[2] * (*this)[3] - (*this)[0] * (*this)[5]) / det,
			((*this)[3] * (*this)[7] - (*this)[4] * (*this)[6]) / det,
			((*this)[1] * (*this)[6] - (*this)[0] * (*this)[7]) / det,
			((*this)[0] * (*this)[4] - (*this)[1] * (*this)[3]) / det };

		Matrix3 inverse = Matrix3(tmp);
		return inverse;
	}

	Matrix3 Matrix3::Transpose() const {
		Matrix3 transpose = Matrix3();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				transpose[i * SIZE + j] = (*this)[j * SIZE + i];
			}
		}
		return transpose;
	}

	void Matrix3::SetOrientation(Quaternion &q) {
		(*this) = Matrix3(q);
	}

	Matrix3 Matrix3::BaseChange(Vector3 &base) {
		Matrix3 baseMatrix = Matrix3(base);
		Matrix3 inverseBaseMatrix = baseMatrix.Inverse();
		return baseMatrix * (*this) * inverseBaseMatrix;
	}
}