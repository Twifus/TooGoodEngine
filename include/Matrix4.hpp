#pragma once
#include "Vector3.hpp"
#include <cmath>

#define DATA_LENGTH 12 
#define SIZE 4

namespace TooGoodEngine {
	class Matrix4
	{
	public:
		Matrix4();											// Construct a null matrix (0,0,0,0,0,0,0,0,0)
		Matrix4(Vector3& vector);							// Construct a matrix from a Vector (x,y,z)
		Matrix4(double matrix[DATA_LENGTH]);				// Construct a matrix from an array of 9 double

		Matrix4 operator+(const Matrix4& matrix) const;	// Addition two matrix component by component,			return a new one

		Vector3 operator*(const Vector3& vector) const;		// Multiplication of a matrix with a Vector				return a new Vector
		Matrix4 operator*(const Matrix4& matrix) const;		// Multiplication of two matrix							return a new one
		Matrix4 operator*(const double k) const;			// Multiplication of all components of the matrix by k	return a new matrix

		Matrix4 operator/(const double k) const;			// Division of all components of the matrix by k		return a new matrix

		double operator[](const int index) const;			// Getter of the component at index index
		double& operator[](const int index);				// Setter of the component at index index

		bool operator==(const Matrix4& matrix) const;		// Comparison of the two matrix component by component
		bool operator!=(const Matrix4& matrix) const;		// Comparison like above

		Matrix4& operator+=(const Matrix4& matrix);			// Addition of a matrix to this							return modified matrix
		Matrix4& operator*=(const Matrix4& matrix);			// Multiplication of this with another matrix			return modified matrix
		Matrix4& operator*=(const double k);				// Multiplication of this with constant k				return modified matrix
		Matrix4& operator/=(const double k);				// Division of this with constant k						return modified matrix

		double ComputeDet() const;							// Computation of the determinant of this
		bool IsInvertible() const;							// Test if a matrix is invertible
		Matrix4 Inverse() const;							// Computation of the inverse matrix					return a new one
		Matrix4 Transpose() const;							// Transposition of this								return a new matrix
		Matrix4 BaseChange(Vector3& base);					// Base changement of this								return a new matrix

	private:
		double m_data[DATA_LENGTH];
	};
}