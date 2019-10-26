#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

#include "Quaternion.hpp"

bool is_near(double x, double from)
{
	return x <= from + std::numeric_limits<double>::epsilon() && x >= from - std::numeric_limits<double>::epsilon();
}

namespace TooGoodEngine
{
	class TestQuaternion
	{
	public:
		static void TestConstructor()
		{
			// We don't check that the quaternions are well defined (squared sum = 1), we just test if the values are stored correctly
			const Quaternion
				q0,
				q1(1, 2, 3, 4),
				q2(-10.5f, 9.35, 4 / 5, 0.);
			assert(q0.w == 0 && q0.x == 0 && q0.y == 0 && q0.z == 0);
			assert(q1.w == 1 && q1.x == 2 && q1.y == 3 && q1.z == 4);
			assert(q2.w == -10.5f && q2.x == 9.35 && q2.y == 4 / 5 && q2.z == 0);
		}

		static void TestAxisAngle()
		{
			const Quaternion
				q0 = Quaternion::AxisAngle(Vector3(1, 0, 0), M_PI),
				q1 = Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI),
				q2 = Quaternion::AxisAngle(Vector3(0, 0, 1), M_PI);
			
			assert(is_near(q0.w, 0) && is_near(q0.x, 1) && is_near(q0.y, 0) && is_near(q0.z, 0));
			assert(is_near(q1.w, 0) && is_near(q1.x, 0) && is_near(q1.y, 1) && is_near(q1.z, 0));
			assert(is_near(q2.w, 0) && is_near(q2.x, 0) && is_near(q2.y, 0) && is_near(q2.z, 1));
		}

		static void TestComparison()
		{
			const Quaternion
				q0(1, 2, 3, 4),
				q1(1, 2, 3, 4),
				q2(0, 2, 3, 4),
				q3(1, 0, 3, 4),
				q4(1, 2, 0, 4),
				q5(1, 2, 3, 0);

			assert(q0 == q0);
			assert(!(q0 != q0));

			assert(q0 == q1);
			assert(!(q0 != q1));

			assert(!(q0 == q2));
			assert(q0 != q2);

			assert(!(q0 == q3));
			assert(q0 != q3);

			assert(!(q0 == q4));
			assert(q0 != q4);

			assert(!(q0 == q5));
			assert(q0 != q5);
		}

		static void TestBasicOperators()
		{
			const Quaternion
				q0(2, 2, 2, 2),
				q1(4, 8, 16, 32),
				q2(0, 0, 0, 0);

			assert(q1 + q0 == Quaternion(6, 10, 18, 34));
			assert(q1 - q0 == Quaternion(2, 6, 14, 30));
			assert(q1 * q0 == Quaternion(-104, -8, 88, 56));

			assert(+q0 == Quaternion(2, 2, 2, 2));
			assert(-q0 == Quaternion(-2, -2, -2, -2));
		}

		static void TestScalarOperators()
		{
			const Quaternion q0(2, 2, 2, 2);

			assert(2 * q0 == Quaternion(4, 4, 4, 4));
			assert(q0 * 2 == Quaternion(4, 4, 4, 4));
			assert(q0 / 2 == Quaternion(1, 1, 1, 1));

			Quaternion q = q0 / 0;
			assert(std::isinf(q.w) && std::isinf(q.x) && std::isinf(q.y) && std::isinf(q.z));
		}

		static void TestAffectationOperators()
		{
			const Quaternion
				q0(4, 8, 16, 32),
				q1(2, 2, 2, 2);
			Quaternion q2(4, 8, 16, 32);

			assert((q2 = q1) == q1);

			q2 = q0;
			assert((q2 += q1) == Quaternion(6, 10, 18, 34));

			q2 = q0;
			assert((q2 -= q1) == Quaternion(2, 6, 14, 30));

			q2 = q0;
			assert((q2 *= q1) == Quaternion(-104, -8, 88, 56));
		}

		static void TestLogExpPow()
		{
			const Quaternion
				q0(1, 0, 0, 0),
				q1(0, 1, 0, 0),
				q2(0, 0, 1, 0),
				q3(0, 0, 0, 1);

			{
				assert(Quaternion::Log(q0) == Quaternion(0, 0, 0, 0));
				assert(Quaternion::Log(q1) == Quaternion(0, M_PI_2, 0, 0));
				assert(Quaternion::Log(q2) == Quaternion(0, 0, M_PI_2, 0));
				assert(Quaternion::Log(q3) == Quaternion(0, 0, 0, M_PI_2));
			}
			
			{
				assert(Quaternion::Exp(q0) == Quaternion(std::exp(1), 0, 0, 0));
				assert(Quaternion::Exp(q1) == Quaternion(std::cos(1), std::sin(1), 0, 0));
				assert(Quaternion::Exp(q2) == Quaternion(std::cos(1), 0, std::sin(1), 0));
				assert(Quaternion::Exp(q3) == Quaternion(std::cos(1), 0, 0, std::sin(1)));
			}

			{
				assert(q0.Pow(2) == q0);

				const Quaternion
					qr1 = q1.Pow(2),
					qr2 = q2.Pow(2),
					qr3 = q3.Pow(2);
				assert(is_near(qr1.w, -1) && is_near(qr1.x, 0) && is_near(qr1.y, 0) && is_near(qr1.z, 0));
				assert(is_near(qr2.w, -1) && is_near(qr2.x, 0) && is_near(qr2.y, 0) && is_near(qr2.z, 0));
				assert(is_near(qr3.w, -1) && is_near(qr3.x, 0) && is_near(qr3.y, 0) && is_near(qr3.z, 0));
			}

			{
				const Quaternion q(2, 0, 0, 0);
				assert(q0.Pow(q) == q0.Pow(2));
				assert(q1.Pow(q) == q1.Pow(2));
				assert(q2.Pow(q) == q2.Pow(2));
				assert(q3.Pow(q) == q3.Pow(2));
			}
		}

		static void TestDot()
		{
			const Quaternion
				q0(1, 2, 3, 4),
				q1(5, 6, 7, 8);

			assert(q0.Dot(q1) == 70);
		}

		static void TestAngle()
		{
			const Quaternion
				q0(1, 0, 0, 0),
				q1(0, 1, 0, 0),
				q2(0, 0, 1, 0),
				q3(0, 0, 0, 1);

			assert(Quaternion::Angle(q0, q0) == 0);
			assert(Quaternion::Angle(q0, q1) == M_PI);
			assert(Quaternion::Angle(q0, q2) == M_PI);
			assert(Quaternion::Angle(q0, q3) == M_PI);
		}

		static void TestDelta()
		{
			const Quaternion
				q0(1, 0, 0, 0),
				q1(0, 1, 0, 0),
				q2(0, 0, 1, 0),
				q3(0, 0, 0, 1);

			assert(Quaternion::Delta(q0, q0) == q0);
			assert(Quaternion::Delta(q0, q1) == q1);
			assert(Quaternion::Delta(q0, q2) == q2);
			assert(Quaternion::Delta(q0, q3) == q3);
		}

		static void TestMagnitude()
		{
			const Quaternion
				q0(10, 0, 0, 0),
				q1(0, 10, 0, 0),
				q2(0, 0, 10, 0),
				q3(0, 0, 0, 10),
				q4(0, -5, 0, 0),
				q5(1, 1, 1, 1),
				q6(0, 0, 0, 0);

			assert(q0.SquaredMagnitude() == 100 && q0.Magnitude() == 10);
			assert(q1.SquaredMagnitude() == 100 && q1.Magnitude() == 10);
			assert(q2.SquaredMagnitude() == 100 && q2.Magnitude() == 10);
			assert(q3.SquaredMagnitude() == 100 && q3.Magnitude() == 10);
			assert(q4.SquaredMagnitude() == 25 && q4.Magnitude() == 5);
			assert(q5.SquaredMagnitude() == 4 && q5.Magnitude() == 2);
			assert(q6.SquaredMagnitude() == 0 && q6.Magnitude() == 0);
		}

		static void TestNormalized()
		{
			const Quaternion
				q0(10, 0, 0, 0),
				q1(0, 10, 0, 0),
				q2(0, 0, 10, 0),
				q3(0, 0, 0, 10),
				q4(1, 1, 1, 1),
				q5(0, 0, 0, 0);

			assert(q0.Normalized() == Quaternion(1, 0, 0, 0));
			assert(q1.Normalized() == Quaternion(0, 1, 0, 0));
			assert(q2.Normalized() == Quaternion(0, 0, 1, 0));
			assert(q3.Normalized() == Quaternion(0, 0, 0, 1));

			assert(q4.Normalized() == Quaternion(0.5, 0.5, 0.5, 0.5));

			Quaternion q = q5.Normalized();
			assert(std::isnan(q.w) && std::isnan(q.x) && std::isnan(q.y) && std::isnan(q.z));
		}
	};
}

int main(int argc, char* argv[])
{
	using namespace TooGoodEngine;
	TestQuaternion::TestConstructor();
	TestQuaternion::TestAxisAngle();
	TestQuaternion::TestComparison();
	TestQuaternion::TestBasicOperators();
	TestQuaternion::TestScalarOperators();
	TestQuaternion::TestAffectationOperators();
	TestQuaternion::TestLogExpPow();
	TestQuaternion::TestDot();
	TestQuaternion::TestAngle();
	TestQuaternion::TestDelta();
	TestQuaternion::TestMagnitude();
	TestQuaternion::TestNormalized();
	return EXIT_SUCCESS;
}