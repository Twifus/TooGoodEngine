#include "Matrix3.hpp"

namespace TooGoodEngine {
	Matrix3::Matrix3() : data({0}) {}
	Matrix3::Matrix3(double matrix[DATA_LENGTH]) : data(matrix) {}
	Matrix3::Matrix3(Vector3 &vector) : data({vector.x, 0, 0, 0, vector.y, 0, 0, 0, vector.z}) {}
	Matrix3::Matrix3(Quaternion &q) : data({1 - (2 * q.y * q.y + 2 * q.z * q.z),
											2 * q.x * q.y + 2 * q.z * q.w,
											2 * q.x * q.z - 2 * q.y * q.w,
											2 * q.x * q.y - 2 * q.z * q.w,
											1 - (2 * q.x * q.x + 2 * q.z * q.z),
											2 * q.y * q.z + 2 * q.x * q.w,
											2 * q.x * q.z + 2 * q.y * q.w,
											2 * q.y * q.z - 2 * q.x * q.w,
											1 - (2 * q.x * q.x + 2 * q.y * q.y)}) {}

	
	Matrix3 Matrix3::operator+(const Matrix3 &matrix) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < DATA_LENGTH, i++) {
			result[i] = this[i] + matrix[i];
		}
		return result;
	}

	Vector3 Matrix3::operator*(const Vector3 &vector) const {
		return Vector3(	this[0] * vector.x + this[1] * vector.y + this[2] * vector.z,
						this[3] * vector.x + this[4] * vector.y + this[5] * vector.z,
						this[6] * vector.x + this[7] * vector.y + this[8] * vector.z );
	}

	Matrix3 Matrix3::operator*(const Matrix3 &matrix) const {
		return Matrix3({ this[0] * matrix[0] + this[1] * matrix[3] + this[2] * matrix[6],
						this[0] * matrix[1] + this[1] * matrix[4] + this[2] * matrix[7],
						this[0] * matrix[2] + this[1] * matrix[5] + this[2] * matrix[8],
						this[3] * matrix[0] + this[4] * matrix[3] + this[5] * matrix[6],
						this[3] * matrix[1] + this[4] * matrix[4] + this[5] * matrix[7],
						this[3] * matrix[2] + this[4] * matrix[5] + this[5] * matrix[8],
						this[6] * matrix[0] + this[7] * matrix[3] + this[8] * matrix[6],
						this[6] * matrix[1] + this[7] * matrix[4] + this[8] * matrix[7],
						this[6] * matrix[2] + this[7] * matrix[5] + this[8] * matrix[8] });
	}

	Matrix3 Matrix3::operator*(const double k) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < DATA_LENGTH, i++) {
			result[i] = (*this)[i] * k;
		}
		return result;
	}

	Matrix3 Matrix3::operator/(const double k) const {
		Matrix3 result = Matrix3();
		for (int i = 0; i < DATA_LENGTH, i++) {
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

	Matrix3& Matrix3::operator+=(const Matrix3 &matrix) const {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] += matrix[i];
		return *this;
	}

	Matrix3& Matrix3::operator*=(const Matrix3 &matrix) const {
		*this = ((*this) * matrix);
		return *this;
	}

	Matrix3& Matrix3::operator*=(const double k) const {
		for (int i = 0; i < DATA_LENGTH; i++) (*this)[i] *= k;
		return *this;
	}

	Matrix3& Matrix3::operator/=(const double k) const {
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

	bool Matrix3::IsInversible() const {
		return (this->ComputeDet() != 0);
	}

	Matrix3 Matrix3::Inverse() const {
		double det = this->ComputeDet();
		Matrix3 inverse = Matrix3({ ((*this)[4] * (*this)[8] - (*this)[5] * (*this)[7]) / det,
			((*this)[2] * (*this)[7] - (*this)[1] * (*this)[8]) / det,
			((*this)[1] * (*this)[5] - (*this)[2] * (*this)[4]) / det,
			((*this)[5] * (*this)[6] - (*this)[3] * (*this)[8]) / det,
			((*this)[0] * (*this)[8] - (*this)[2] * (*this)[6]) / det,
			((*this)[2] * (*this)[3] - (*this)[0] * (*this)[5]) / det,
			((*this)[3] * (*this)[7] - (*this)[4] * (*this)[6]) / det,
			((*this)[1] * (*this)[6] - (*this)[0] * (*this)[7]) / det,
			((*this)[0] * (*this)[4] - (*this)[1] * (*this)[3]) / det });
		return (inverse / inverse.ComputeDet());
	}
}