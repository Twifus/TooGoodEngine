#include "Matrix4.hpp"

namespace TooGoodEngine {
	Matrix4::Matrix4() {
		for (int i = 0; i < DATA_LENGTH; i++) data[i] = 0;
	}

	Matrix4::Matrix4(double matrix[DATA_LENGTH]) {
		for (int i = 0; i < DATA_LENGTH; i++) data[i] = matrix[i];
	}
	Matrix4::Matrix4(Vector3 &vector) {
		for (int i = 0; i < DATA_LENGTH; i++) {
			data[i] = 0;
			if (i == SIZE - 1)	   data[i] = vector.x;
			if (i == SIZE * 2 - 1) data[i] = vector.y;
			if (i == SIZE * 3 - 1) data[i] = vector.z;
		}
	}

	Matrix4 Matrix4::operator+(const Matrix4 &matrix) const {
		Matrix4 result = Matrix4();
		for (int i = 0; i < DATA_LENGTH; i++) {
			result[i] = (*this)[i] + matrix[i];
		}
		return result;
	}

	Vector3 Matrix4::operator*(const Vector3 &vector) const {
		return Vector3((*this)[0] * vector.x + (*this)[1] * vector.y + (*this)[2] * vector.z,
			(*this)[4] * vector.x + (*this)[5] * vector.y + (*this)[6] * vector.z,
			(*this)[8] * vector.x + (*this)[9] * vector.y + (*this)[10] * vector.z);
	}

	Matrix4 Matrix4::operator*(const Matrix4 &matrix) const {
		double tmp[DATA_LENGTH] = { (*this)[0] * matrix[0] + (*this)[1] * matrix[4] + (*this)[2] * matrix[8],
						(*this)[0] * matrix[1] + (*this)[1] * matrix[5] + (*this)[2] * matrix[9],
						(*this)[0] * matrix[2] + (*this)[1] * matrix[6] + (*this)[2] * matrix[10],
						(*this)[0] * matrix[3] + (*this)[1] * matrix[7] + (*this)[2] * matrix[11] + (*this)[3],
						(*this)[4] * matrix[0] + (*this)[5] * matrix[4] + (*this)[6] * matrix[8],
						(*this)[4] * matrix[1] + (*this)[5] * matrix[5] + (*this)[6] * matrix[9],
						(*this)[4] * matrix[2] + (*this)[5] * matrix[6] + (*this)[6] * matrix[10],
						(*this)[4] * matrix[3] + (*this)[5] * matrix[7] + (*this)[6] * matrix[11] + (*this)[7],
						(*this)[8] * matrix[0] + (*this)[9] * matrix[4] + (*this)[10] * matrix[8],
						(*this)[8] * matrix[1] + (*this)[9] * matrix[5] + (*this)[10] * matrix[9],
						(*this)[8] * matrix[2] + (*this)[9] * matrix[6] + (*this)[10] * matrix[10],
						(*this)[8] * matrix[3] + (*this)[9] * matrix[7] + (*this)[10] * matrix[11] + (*this)[11] };

		return Matrix4(tmp);
	}

	Matrix4 Matrix4::operator*(const double k) const {
		Matrix4 result = Matrix4();
		for (int i = 0; i < DATA_LENGTH; i++) {
			result[i] = (*this)[i] * k;
		}
		return result;
	}

	Matrix4 Matrix4::operator/(const double k) const {
		Matrix4 result = Matrix4();
		for (int i = 0; i < DATA_LENGTH; i++) {
			result[i] = (*this)[i] / k;
		}
		return result;
	}

	double Matrix4::operator[](const int index) const {
		return this->data[index];
	}

	double& Matrix4::operator[](const int index) {
		return this->data[index];
	}

	bool Matrix4::operator==(const Matrix4 &matrix) const {
		for (int i = 0; i < DATA_LENGTH; i++) {
			if ((*this)[i] != matrix[i]) return false;
		}
		return true;
	}

	bool Matrix4::operator!=(const Matrix4 &matrix) const {
		return !((*this) == matrix);
	}

	Matrix4& Matrix4::operator+=(const Matrix4 &matrix) {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] += matrix[i];
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4 &matrix) {
		*this = ((*this) * matrix);
		return *this;
	}

	Matrix4& Matrix4::operator*=(const double k) {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] *= k;
		return *this;
	}

	Matrix4& Matrix4::operator/=(const double k) {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] /= k;
		return *this;
	}

	double Matrix4::ComputeDet() const {
		return ((*this)[8] * (*this)[5] * (*this)[2] +
			(*this)[4] * (*this)[9] * (*this)[2] +
			(*this)[8] * (*this)[1] * (*this)[6] -
			(*this)[0] * (*this)[9] * (*this)[6] -
			(*this)[4] * (*this)[1] * (*this)[10] -
			(*this)[0] * (*this)[5] * (*this)[10]);
	}

	bool Matrix4::IsInvertible() const {
		return (this->ComputeDet() != 0);
	}

	Matrix4 Matrix4::Inverse() const {
		double det = this->ComputeDet();

		// Compute values at index 3, 7 and 11
		double index3 = ((*this)[9] * (*this)[6] * (*this)[3] +
			(*this)[1] * (*this)[10] * (*this)[7] +
			(*this)[5] * (*this)[2] * (*this)[11] -
			(*this)[5] * (*this)[10] * (*this)[3] -
			(*this)[9] * (*this)[2] * (*this)[7] -
			(*this)[1] * (*this)[6] * (*this)[11]) / det;

		double index7 = ((*this)[4] * (*this)[10] * (*this)[3] +
			(*this)[8] * (*this)[2] * (*this)[7] +
			(*this)[0] * (*this)[6] * (*this)[11] -
			(*this)[8] * (*this)[6] * (*this)[3] -
			(*this)[0] * (*this)[10] * (*this)[7] -
			(*this)[4] * (*this)[2] * (*this)[11]) / det;

		double index11 = ((*this)[8] * (*this)[5] * (*this)[3] +
			(*this)[0] * (*this)[9] * (*this)[7] +
			(*this)[4] * (*this)[1] * (*this)[11] -
			(*this)[0] * (*this)[5] * (*this)[11] -
			(*this)[4] * (*this)[9] * (*this)[3] -
			(*this)[8] * (*this)[1] * (*this)[7]) / det;

		// Creates an array of the component of the inverse matrix
		double tmp[DATA_LENGTH] = { ((*this)[5] * (*this)[10] - (*this)[9] * (*this)[6]) / det,
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
			index11 };

		Matrix4 inverse = Matrix4(tmp);
		return inverse;
	}

	Matrix4 Matrix4::Transpose() const {
		Matrix4 transpose = Matrix4();
		for (int i = 0; i < SIZE - 1; i++) {
			for (int j = 0; j < SIZE; j++) {
				transpose[i * SIZE + j] = (*this)[j * SIZE + i];
			}
		}
		return transpose;
	}

	Matrix4 Matrix4::BaseChange(Vector3 &base) {
		Matrix4 baseMatrix = Matrix4(base);
		Matrix4 inverseBaseMatrix = baseMatrix.Inverse();
		return baseMatrix * (*this) * inverseBaseMatrix;
	}
}