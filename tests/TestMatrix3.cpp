#include "Matrix3.hpp"

#include <cassert>
#include <cmath>
#include <stdexcept>

namespace TooGoodEngine
{
	class TestMatrix3
	{
	public:
		static void TestConstructor()
		{
			const Vector3 v(1, 2, 3);
			const std::array<double, Matrix3::data_length> a2 
			{ 
				1, 2, 3, 
				4, 5, 6, 
				7, 8, 9 
			};
			const Quaternion q(1, 2, 3, 4);
			
			const Matrix3
				m0,
				m1(v),
				m2(a2),
				m3(q);

			std::array<double, Matrix3::data_length> a0 
			{ 
				0, 0, 0, 
				0, 0, 0, 
				0, 0, 0 
			};
			assert(m0.data() == a0);

			std::array<double, Matrix3::data_length> a1 
			{ 
				1, 0, 0, 
				0, 2, 0, 
				0, 0, 3 
			};
			assert(m1.data() == a1);

			assert(m2.data() == a2);

			std::array<double, Matrix3::data_length> a3
			{
				-49,  20,  10,
				  4, -39,  28,
				 22,  20, -25
			};
			assert(m3.data() == a3);
		}

		static void TestComparison()
		{
			const std::array<double, Matrix3::data_length> a0
			{
				1, 2, 3,
				4, 5, 6,
				7, 8, 9
			};
			const std::array<double, Matrix3::data_length> a1
			{
				1, 2, 3,
				4, 5, 6,
				7, 8, 9
			};

			const Matrix3
				m0(a0),
				m1(a1);

			assert(m0 == m0);
			assert(!(m0 != m0));

			assert(m1 == m0);
			assert(!(m1 != m0));

			std::array<Matrix3, Matrix3::data_length> ms;
			for (int i = 0; i < 9; ++i)
			{
				std::array<double, Matrix3::data_length> a(a0);
				a[i] = 0;
				ms[i] = Matrix3(a);
				assert(ms[i] != m0);
				assert(!(ms[i] == m0));
			}
		}

		static void TestAccessors()
		{
			const Matrix3 m0({ 0, 1, 2, 3, 4, 5, 6, 7, 8 });
			Matrix3 m1;

			for (int i = 0; i < Matrix3::data_length; ++i)
			{
				assert(m0[i] == i);
				m1[i] = i;
				assert(m1[i] == i);
			}
		}

		static void TestMatrixToMatrixOperators()
		{
			const Matrix3
				m0({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }),
				m1({ 0, 1, 2, 3, 4, 5, 6, 7, 8 });

			assert(m1 + m0 == Matrix3({ 0, 2, 4, 6, 8, 10, 12, 14, 16 }));
			assert(m1 - m0 == Matrix3({ 0, 0, 0, 0, 0, 0, 0, 0, 0 }));
			assert(m1 * m0 == Matrix3({ 15, 18, 21, 42, 54, 66, 69, 90, 111 }));
		}

		static void TestMatrixToScalarOperator()
		{
			const Matrix3 m0({ 2, 4, 6, 8, 10, 12, 14, 16, 18 });

			assert(m0 * 2 == Matrix3({ 4, 8, 12, 16, 20, 24, 28, 32, 36 }));
			assert(m0 / 2 == Matrix3({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }));
		}

		static void TestAffectationOperators()
		{
			const Matrix3 m({ 2, 4, 6, 8, 10, 12, 14, 16, 18 });
			Matrix3
				m0({ 2, 4, 6, 8, 10, 12, 14, 16, 18 }),
				m1({ 0, 1, 2, 3, 4, 5, 6, 7, 8 });

			assert((m0 += m) == Matrix3({ 4, 8, 12, 16, 20, 24, 28, 32, 36 }));
			m0 = m;
			assert((m0 -= m) == Matrix3({ 0, 0, 0, 0, 0, 0, 0, 0, 0 }));
			m0 = m;
			assert((m0 *= 2) == Matrix3({ 4, 8, 12, 16, 20, 24, 28, 32, 36 }));
			m0 = m;
			assert((m0 /= 2) == Matrix3({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

			assert((m1 *= m1) == Matrix3({ 15, 18, 21, 42, 54, 66, 69, 90, 111 }));
		}

		static void TestInverse()
		{
			const Matrix3
				m0 = Matrix3::identity,
				m1({ 1, 2, 3, 0, 1, 4, 5, 6, 0 }),
				m2;

			assert(m0.IsInvertible() && m0.Inverse() == m0);
			assert(m1.IsInvertible() && m1.Inverse() == Matrix3({ -24, 18, 5, 20, -15, -4, -5, 4, 1 }));
			assert(!m2.IsInvertible());
		}

		static void TestTranspose()
		{
			const Matrix3 m({ 0, 1, 2, 3, 4, 5, 6, 7, 8 });

			assert(m.Transpose() == Matrix3({ 0, 3, 6, 1, 4, 7, 2, 5, 8 }));
		}
	};
}

int main(int argc, char *argv[])
{
	using namespace TooGoodEngine;
	TestMatrix3::TestConstructor();
	TestMatrix3::TestComparison();
	TestMatrix3::TestAccessors();
	TestMatrix3::TestMatrixToMatrixOperators();
	TestMatrix3::TestMatrixToScalarOperator();
	TestMatrix3::TestAffectationOperators();
	TestMatrix3::TestInverse();
	TestMatrix3::TestTranspose();
	return EXIT_SUCCESS;
}