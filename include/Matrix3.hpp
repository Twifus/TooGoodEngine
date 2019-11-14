#pragma once
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include <cmath>
#include <array>

namespace TooGoodEngine {
	class Matrix3
	{
	public:
		static constexpr int size = 3;						// size of the matrix
		static constexpr int data_length = size * size;		// total number of data in the matrix

		static const Matrix3 identity;

		Matrix3();											// Construct a null matrix (0,0,0,0,0,0,0,0,0)
		Matrix3(const std::array<double, Matrix3::data_length> matrix);	// Construct a matrix from an array of 9 double
		Matrix3(const double matrix[Matrix3::data_length]);				// Construct a matrix from an array of 9 double
		Matrix3(const Quaternion& q);						// Construct a matrix from a Quaternion 
		Matrix3(const Vector3& vector);						// Construct a matrix from a Vector (x,y,z)

		const std::array<double, Matrix3::data_length> data() const;	// return the content of this matrix

		bool operator==(const Matrix3& matrix) const;		// Comparison of the two matrix component by component
		bool operator!=(const Matrix3& matrix) const;		// Comparison like above

		double operator[](const int index) const;			// Getter of the component at index index
		double& operator[](const int index);				// Setter of the component at index index

		Matrix3 operator+(const Matrix3& matrix) const;		// Addition of two matrix component by component,		return a new one
		Matrix3 operator-(const Matrix3& matrix) const;		// Subtraction of two matrix component by component,	return a new one

		Vector3 operator*(const Vector3& vector) const;		// Multiplication of a matrix with a Vector				return a new Vector
		Matrix3 operator*(const Matrix3& matrix) const;		// Multiplication of two matrix							return a new one
		Matrix3 operator*(const double k) const;			// Multiplication of all components of the matrix by k	return a new matrix

		Matrix3 operator/(const double k) const;			// Division of all components of the matrix by k		return a new matrix

		Matrix3& operator+=(const Matrix3& matrix);			// Addition of a matrix to this							return modified matrix
		Matrix3& operator-=(const Matrix3& matrix);			// Addition of a matrix to this							return modified matrix
		Matrix3& operator*=(const Matrix3& matrix);			// Multiplication of this with another matrix			return modified matrix
		Matrix3& operator*=(const double k);				// Multiplication of this with constant k				return modified matrix
		Matrix3& operator/=(const double k);				// Division of this with constant k						return modified matrix

		double ComputeDet() const;							// Computation of the determinant of this
		bool IsInvertible() const;							// Test if a matrix is invertible
		Matrix3 Inverse() const;							// Computation of the inverse matrix					return a new one
		Matrix3 Transpose() const;							// Transposition of this								return a new matrix
		void SetOrientation(Quaternion& q);					// Modification of this depending on a Quaternion		return void
		
	private:
		std::array<double, Matrix3::data_length> m_data;
	};
}