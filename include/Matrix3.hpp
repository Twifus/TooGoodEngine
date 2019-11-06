#pragma once
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include <cmath>

#define DATA_LENGTH 9 

namespace TooGoodEngine {
	class Matrix3
	{
	public:
		Matrix3();
		Matrix3(Quaternion &q);
		Matrix3(Vector3 &vector);
		Matrix3(double matrix[DATA_LENGTH]);

		Matrix3 operator+(const Matrix3 & matrix) const;

		Vector3 operator*(const Vector3 &vector) const;
		Matrix3 operator*(const Matrix3 &matrix) const;
		Matrix3 operator*(const double k) const;

		Matrix3 operator/(const double k) const;

		double operator[](const int index) const;
		double& operator[](const int index);

		bool operator==(const Matrix3 &matrix) const;
		bool operator!=(const Matrix3 &matrix) const;

		Matrix3& operator+=(const Matrix3 &matrix);
		Matrix3& operator*=(const Matrix3 &matrix);
		Matrix3& operator*=(const double k);
		Matrix3& operator/=(const double k);

		double ComputeDet() const;
		bool IsInversible() const;
		Matrix3 Inverse() const;
		Matrix3 Transpose() const;
		Matrix3 SetOrientation(Quaternion &q) const;
		Matrix3 BaseChange(Vector3 &base);


	private:
		double data[DATA_LENGTH];
	};
}