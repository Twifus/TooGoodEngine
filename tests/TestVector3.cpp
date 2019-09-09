#include "Vector3.hpp"

#include <cassert>
#include <stdexcept>
#include <limits>

namespace TooGoodEngine
{
	class TestVector3
	{
	public:
		static void TestConstructor()
		{
			const Vector3
				v0,
				v1(1, 2, 3),
				v2(-10.5f, 9.35, 4 / 5);
			assert(v0.x == 0 && v0.y == 0 && v0.z == 0);
			assert(v1.x == 1 && v1.y == 2 && v1.z == 3);
			assert(v2.x == -10.5f && v2.y == 9.35 && v2.z == 4 / 5);
		}

		static void TestComparison()
		{
			const Vector3
				v0(1, 2, 3),
				v1(1, 2, 3),
				v2(0, 2, 3),
				v3(1, 0, 3),
				v4(1, 2, 0);

			assert(v0 == v0);
			assert(!(v0 != v0));

			assert(v0 == v1);
			assert(!(v0 != v1));

			assert(!(v0 == v2));
			assert(v0 != v2);

			assert(!(v0 == v3));
			assert(v0 != v3);

			assert(!(v0 == v4));
			assert(v0 != v4);
		}

		static void TestVectorToVectorOperators()
		{
			const Vector3
				v0(2, 2, 2),
				v1(4, 8, 16),
				v2(0, 0, 0);

			assert(v1 + v0 == Vector3(6, 10, 18));
			assert(v1 - v0 == Vector3(2, 6, 14));
			assert(v1 * v0 == Vector3(8, 16, 32));
			assert(v1 / v0 == Vector3(2, 4, 8));

			assert(-v0 == Vector3(-2, -2, -2));

			Vector3 v = v1 / v2;
			assert(isinf(v.x) && isinf(v.y) && isinf(v.z));
		}

		static void TestVectorToScalarOperator()
		{
			const Vector3 v0(2, 2, 2);

			assert(2 * v0 == Vector3(4, 4, 4));
			assert(v0 * 2 == Vector3(4, 4, 4));
			assert(v0 / 2 == Vector3(1, 1, 1));

			Vector3 v = v0 / 0;
			assert(isinf(v.x) && isinf(v.y) && isinf(v.z));
		}

		static void TestAffectationOperators()
		{
			const Vector3
				v0(4, 8, 16),
				v1(2, 2, 2);
			Vector3 v2(4, 8, 16);
			Vector3* p = &v2;

			assert((v2 = v1) == v1);

			v2 = v0;
			assert((v2 += v1) == Vector3(6, 10, 18));

			v2 = v0;
			assert((v2 -= v1) == Vector3(2, 6, 14));

			v2 = v0;
			assert((v2 *= v1) == Vector3(8, 16, 32));

			v2 = v0;
			assert((v2 /= v1) == Vector3(2, 4, 8));
		}

		static void TestIndexAccessor()
		{
			const Vector3 v0(0, 1, 2);
			Vector3 v1(0, 1, 2);

			assert(v0[0] == 0);
			assert(v0[1] == 1);
			assert(v0[2] == 2);

			try
			{
				double x = v0[-1];
				assert(false);
			}
			catch (const std::exception & e)
			{
				assert(typeid(e) == typeid(std::out_of_range));
			}

			try
			{
				double x = v0[3];
				assert(false);
			}
			catch (const std::exception & e)
			{
				assert(typeid(e) == typeid(std::out_of_range));
			}
		}

		static void TestDot()
		{
			const Vector3
				v0(1, 2, 3),
				v1(4, 5, 6);

			assert(Vector3::Dot(v0, v1) == 32);
		}

		static void TestCross()
		{
			const Vector3
				v0(1, 0, 0),
				v1(0, 1, 0),
				v2(0, 0, 1);

			assert(Vector3::Cross(v0, v1) == v2);
			assert(Vector3::Cross(v1, v2) == v0);
			assert(Vector3::Cross(v2, v0) == v1);
		}

		static void TestMagnitude()
		{
			const Vector3
				v0(10, 0, 0),
				v1(0, 10, 0),
				v2(0, 0, 10),
				v3(0, -5, 0),
				v4(1, 1, 1),
				v5(0, 0, 0);

			assert(v0.SquaredMagnitude() == 100 && v0.Magnitude() == 10);
			assert(v1.SquaredMagnitude() == 100 && v1.Magnitude() == 10);
			assert(v2.SquaredMagnitude() == 100 && v2.Magnitude() == 10);
			assert(v3.SquaredMagnitude() == 25 && v3.Magnitude() == 5);
			assert(v4.SquaredMagnitude() == 3 && v4.Magnitude() == std::sqrt(3));
			assert(v5.SquaredMagnitude() == 0 && v5.Magnitude() == 0);
		}

		static void TestNormalized()
		{
			const Vector3
				v0(10, 0, 0),
				v1(0, 10, 0),
				v2(0, 0, 10),
				v3(1, 1, 1),
				v4(0, 0, 0);

			assert(v0.Normalized() == Vector3(1, 0, 0));
			assert(v1.Normalized() == Vector3(0, 1, 0));
			assert(v2.Normalized() == Vector3(0, 0, 1));

			double x = 1 / std::sqrt(3);
			assert(v3.Normalized() == Vector3(x, x, x));

			Vector3 v = v4.Normalized();
			assert(isnan(v.x) && isnan(v.y) && isnan(v.z));
		}
	};
}

int main(int argc, char *argv[])
{
	using namespace TooGoodEngine;
	TestVector3::TestConstructor();
	TestVector3::TestComparison();
	TestVector3::TestVectorToVectorOperators();
	TestVector3::TestVectorToScalarOperator();
	TestVector3::TestAffectationOperators();
	TestVector3::TestIndexAccessor();
	TestVector3::TestDot();
	TestVector3::TestCross();
	TestVector3::TestMagnitude();
	TestVector3::TestNormalized();
	return EXIT_SUCCESS;
}