#include "Matrix4.hpp"

#include <cassert>
#include <cmath>
#include <stdexcept>

namespace TooGoodEngine
{
	class TestMatrix4
	{
	public:
		static void TestConstructor()
		{
			const Vector3 v(1, 2, 3);
			const std::array<double, Matrix4::data_length> a2 
			{ 
				1,  2,  3,  4,
				5,  6,  7,  8,
				9, 10, 11, 12
			};
			const Quaternion q(1, 2, 3, 4);
			const Matrix3 m({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
			
			const Matrix4
				m0,
				m1(v),
				m2(a2),
				m3(m, v),
				m4(q, v);

			std::array<double, Matrix4::data_length> a0 
			{ 
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
			};
			assert(m0.data() == a0);

			std::array<double, Matrix4::data_length> a1 
			{ 
				0, 0, 0, 1,
				0, 0, 0, 2,
				0, 0, 0, 3
			};
			assert(m1.data() == a1);

			assert(m2.data() == a2);

			std::array<double, Matrix4::data_length> a3
			{
				1, 2, 3, 1,
				4, 5, 6, 2,
				7, 8, 9, 3
			};
			assert(m3.data() == a3);

			std::array<double, Matrix4::data_length> a4
			{
				-49,  20,  10, 1,
				  4, -39,  28, 2,
				 22,  20, -25, 3
			};
			assert(m4.data() == a4);
		}

		static void TestComparison()
		{
			const std::array<double, Matrix4::data_length> a0
			{
				1,  2,  3,  4,
				5,  6,  7,  8,
				9, 10, 11, 12
			};
			const std::array<double, Matrix4::data_length> a1
			{
				1,  2,  3,  4,
				5,  6,  7,  8,
				9, 10, 11, 12
			};

			const Matrix4
				m0(a0),
				m1(a1);

			assert(m0 == m0);
			assert(!(m0 != m0));

			assert(m1 == m0);
			assert(!(m1 != m0));

			for (int i = 0; i < Matrix4::data_length; ++i)
			{
				std::array<double, Matrix4::data_length> a(a0);
				a[i] = 0;
				Matrix4 m(a);
				assert(m != m0);
				assert(!(m == m0));
			}
		}

		static void TestAccessors()
		{
			const Matrix4 m0({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
			Matrix4 m1;

			for (int i = 0; i < Matrix4::data_length; ++i)
			{
				assert(m0[i] == i);
				m1[i] = i;
				assert(m1[i] == i);
			}
		}

		static void TestMatrixToMatrixOperators()
		{
			const Matrix4
				m0({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }),
				m1({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });

			assert(m1 + m0 == Matrix4({ 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22 }));
			assert(m1 - m0 == Matrix4({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }));
			assert(m1 * m0 == Matrix4({ 20, 23, 26, 32, 68, 83, 98, 120, 116, 143, 170, 208 }));
		}

		static void TestMatrixToScalarOperator()
		{
			const Matrix4 m0({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24});

			assert(m0 * 2 == Matrix4({ 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48 }));
			assert(m0 / 2 == Matrix4({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }));
		}

		static void TestAffectationOperators()
		{
			const Matrix4 m({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 });
			Matrix4
				m0({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 }),
				m1({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });

			assert((m0 += m) == Matrix4({ 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48 }));
			m0 = m;
			assert((m0 -= m) == Matrix4({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }));
			m0 = m;
			assert((m0 *= 2) == Matrix4({ 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48 }));
			m0 = m;
			assert((m0 /= 2) == Matrix4({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }));

			assert((m1 *= m1) == Matrix4({ 20, 23, 26, 32, 68, 83, 98, 120, 116, 143, 170, 208 }));
		}

		static void TestInverse()
		{
			const Matrix4
				m0 = Matrix4::identity,
				m1({ 1, 2, 3, 0, 0, 1, 4, 0, 5, 6, 0, 0 }),
				m2;

			assert(m0.IsInvertible() && m0.Inverse() == m0);
			assert(m1.IsInvertible() && m1.Inverse() == Matrix4({ -24, 18, 5, 0, 20, -15, -4, 0, -5, 4, 1, 0 }) && m1.Inverse() * m1 == Matrix4::identity);
			assert(!m2.IsInvertible());
		}

		static void TestTranspose()
		{
			const Matrix4 m({ 
				0, 1, 2, 1, 
				3, 4, 5, 2,
				6, 7, 8, 3
				});

			assert(m.Transpose() == Matrix4({ 0, 3, 6, -1, 1, 4, 7, -2, 2, 5, 8, -3 }));
		}
	};
}

int main(int argc, char *argv[])
{
	using namespace TooGoodEngine;
	TestMatrix4::TestConstructor();
	TestMatrix4::TestComparison();
	TestMatrix4::TestAccessors();
	TestMatrix4::TestMatrixToMatrixOperators();
	TestMatrix4::TestMatrixToScalarOperator();
	TestMatrix4::TestAffectationOperators();
	TestMatrix4::TestInverse();
	TestMatrix4::TestTranspose();
	return EXIT_SUCCESS;
}