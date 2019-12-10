#pragma once

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix3.hpp"

namespace TooGoodEngine {
	class Transform
	{
	public:
		static constexpr int size = 4;							// size of the matrix
		static constexpr int data_length = 12;					// total number of data in the matrix

		static const Transform identity;

		Transform();											// Construct a null matrix (0,0,0,0,0,0,0,0,0)
		Transform(const std::array<double, Transform::data_length> matrix);		// Construct a matrix from an array of 9 double
		Transform(const double matrix[Transform::data_length]);					// Construct a matrix from an array of 9 double
		Transform(const Vector3& vector);						// Construct a matrix from a Vector
		Transform(const Matrix3 &m, const Vector3 &v);			// Construct a matrix from a Matrix3 and a Vector
		Transform(const Quaternion &q, const Vector3 &v);		// Construct a matrix from a Quaternion and a Vector

		const std::array<double, Transform::data_length> data() const;		// Return the content of the matrix

		bool operator==(const Transform& matrix) const;			// Comparison of the two matrix component by component
		bool operator!=(const Transform& matrix) const;			// Comparison like above

		double operator[](const int index) const;				// Getter of the component at index index
		double& operator[](const int index);					// Setter of the component at index index

		Vector3 operator*(const Vector3& vector) const;			// Multiplication of a matrix with a Vector				return a new Vector
		Transform operator*(const Transform& matrix) const;		// Multiplication of two matrix							return a new one

		Transform& operator*=(const Transform& matrix);			// Multiplication of this with another matrix			return modified matrix

		double ComputeDet() const;								// Computation of the determinant of this
		bool IsInvertible() const;								// Test if a matrix is invertible
		Transform Inverse() const;								// Computation of the inverse matrix					return a new one

	private:
		std::array<double, Transform::data_length> m_data;
	};
}