#pragma once
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include <cmath>

#define DATA_LENGTH 9 
#define SIZE 3

namespace TooGoodEngine {
	class Matrix3
	{
	public:
		Matrix3();											// Construct a null matrix (0,0,0,0,0,0,0,0,0)
		Matrix3(Quaternion &q);								// Construct a matrix from a Quaternion 
		Matrix3(Vector3 &vector);							// Construct a matrix from a Vector (x,y,z)
		Matrix3(double matrix[DATA_LENGTH]);				// Construct a matrix from an array of 9 double

		Matrix3 operator+(const Matrix3 & matrix) const;	// Addition two matrix component by component,			return a new one

		Vector3 operator*(const Vector3 &vector) const;		// Multiplication of a matrix with a Vector				return a new Vector
		Matrix3 operator*(const Matrix3 &matrix) const;		// Multiplication of two matrix							return a new one
		Matrix3 operator*(const double k) const;			// Multiplication of all components of the matrix by k	return a new matrix

		Matrix3 operator/(const double k) const;			// Division of all components of the matrix by k		return a new matrix

		double operator[](const int index) const;			// Getter of the component at index index
		double& operator[](const int index);				// Setter of the component at index index

		bool operator==(const Matrix3 &matrix) const;		// Comparison of the two matrix component by component
		bool operator!=(const Matrix3 &matrix) const;		// Comparison like above

		Matrix3& operator+=(const Matrix3 &matrix);			// Addition of a matrix to this							return modified matrix
		Matrix3& operator*=(const Matrix3 &matrix);			// Multiplication of this with another matrix			return modified matrix
		Matrix3& operator*=(const double k);				// Multiplication of this with constant k				return modified matrix
		Matrix3& operator/=(const double k);				// Division of this with constant k						return modified matrix

		double ComputeDet() const;							// Computation of the determinant of this
		bool IsInvertible() const;							// Test if a matrix is invertible
		Matrix3 Inverse() const;							// Computation of the inverse matrix					return a new one
		Matrix3 Transpose() const;							// Transposition of this								return a new matrix
		void SetOrientation(Quaternion &q);					// Modification of this depending on a Quaternion		return void
		Matrix3 BaseChange(Vector3 &base);					// Base changement of this								return a new matrix


	private:
		double data[DATA_LENGTH];							// Array of 9 elements
	};
}