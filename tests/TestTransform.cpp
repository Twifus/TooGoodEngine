#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <stdexcept>

#include "Transform.hpp"

namespace TooGoodEngine
{
	class TestTransform
	{
	public:
		static void TestConstructor()
		{
			const std::array<double, Transform::data_length> a
			{
				1,  2,  3,  4,
				5,  6,  7,  8,
				9, 10, 11, 12
			};
			const Vector3 v(1, 2, 3);
			const Quaternion q(1, 2, 3, 4);
			const Matrix3 m({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
			
			const Transform
				m0,
				m1(a.data()),
				m2(a),
				m3(v),
				m4(m, v),
				m5(q, v);

			std::array<double, Transform::data_length> a0 
			{ 
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
			};
			assert(m0.data() == a0);

			assert(m1.data() == a);

			assert(m2.data() == a);

			std::array<double, Transform::data_length> a3
			{
				0, 0, 0, 1,
				0, 0, 0, 2,
				0, 0, 0, 3
			};
			assert(m3.data() == a3);

			std::array<double, Transform::data_length> a4
			{
				1, 2, 3, 1,
				4, 5, 6, 2,
				7, 8, 9, 3
			};
			assert(m4.data() == a4);

			std::array<double, Transform::data_length> a5
			{
				-49,  20,  10, 1,
				  4, -39,  28, 2,
				 22,  20, -25, 3
			};
			assert(m5.data() == a5);
		}

		static void TestComparison()
		{
			const std::array<double, Transform::data_length> a0
			{
				1,  2,  3,  4,
				5,  6,  7,  8,
				9, 10, 11, 12
			};
			const std::array<double, Transform::data_length> a1
			{
				1,  2,  3,  4,
				5,  6,  7,  8,
				9, 10, 11, 12
			};

			const Transform
				m0(a0),
				m1(a1);

			assert(m0 == m0);
			assert(!(m0 != m0));

			assert(m1 == m0);
			assert(!(m1 != m0));

			for (int i = 0; i < Transform::data_length; ++i)
			{
				std::array<double, Transform::data_length> a(a0);
				a[i] = 0;
				Transform m(a);
				assert(m != m0);
				assert(!(m == m0));
			}
		}

		static void TestAccessors()
		{
			const Transform m0({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
			Transform m1;

			for (int i = 0; i < Transform::data_length; ++i)
			{
				assert(m0[i] == i);
				m1[i] = i;
				assert(m1[i] == i);
			}
		}

		static void TestMatrixToMatrixOperators()
		{
			const Transform
				m0({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }),
				m1({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });

			assert(m1 * m0 == Transform({ 20, 23, 26, 6, 68, 83, 98, 8, 116, 143, 170, 22 }));
		}

		static void TestMatrixToVectorOperators()
		{
			const Transform
				m0;
			const Vector3
				v0;
		}

		static void TestAffectationOperators()
		{
			const Transform m({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 });
			Transform
				m0({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 }),
				m1({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });

			assert((m1 *= m1) == Transform({ 20, 23, 26, 32, 68, 83, 98, 120, 116, 143, 170, 208 }));
		}

		static void TestInverse()
		{
			const Transform
				m0 = Transform::identity,
				m1({ 1, 2, 3, 0, 0, 1, 4, 0, 5, 6, 0, 0 }),
				m2;

			assert(m0.IsInvertible() && m0.Inverse() == m0);
			assert(m1.IsInvertible() && m1.Inverse() == Transform({ -24, 18, 5, 0, 20, -15, -4, 0, -5, 4, 1, 0 }) && m1.Inverse() * m1 == Transform::identity);
			assert(!m2.IsInvertible());
		}
	};
}

int main(int argc, char *argv[])
{
	using namespace TooGoodEngine;
	TestTransform::TestConstructor();
	TestTransform::TestComparison();
	TestTransform::TestAccessors();
	TestTransform::TestMatrixToMatrixOperators();
	TestTransform::TestAffectationOperators();
	TestTransform::TestInverse();
	return EXIT_SUCCESS;
}