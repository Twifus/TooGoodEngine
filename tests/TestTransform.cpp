#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <stdexcept>

#include "Transform.hpp"

namespace TooGoodEngine
{
	bool near(const Transform& t1, const Transform& t2)
	{
		Quaternion q1 = t1.GetRotation(), q2 = t2.GetRotation();
		return
			t1.GetPosition() == t2.GetPosition() &&
			std::abs(q1.w - q2.w) < 1e-9 &&
			std::abs(q1.x - q2.x) < 1e-9 &&
			std::abs(q1.y - q2.y) < 1e-9 &&
			std::abs(q1.z - q2.z) < 1e-9;
	}

	class TestTransform
	{
	public:
		static void TestConstructor()
		{
			const Vector3 v(1, 2, 3);
			const Quaternion q(1, 2, 3, 4);
			const Matrix3 m({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

			const Transform
				t0,
				t1(v),
				t2(v, q);

			assert(t0.GetPosition() == Vector3::zero && t0.GetRotation() == Quaternion::identity);

			assert(t1.GetPosition() == v && t1.GetRotation() == Quaternion::identity);

			assert(t2.GetPosition() == v && t2.GetRotation() == q.Normalized());
		}

		static void TestComparison()
		{
			const Vector3 v0(2, 3, 4);
			const Vector3 v1(2, 3, 4);
			const Quaternion q0 = Quaternion::AxisAngle(Vector3(1, 1, 1), M_PI_2);
			const Quaternion q1 = Quaternion::AxisAngle(Vector3(1, 1, 1), M_PI_2);

			const Transform
				t0(v0, q0),
				t1(v1, q1);

			assert(t0 == t0);
			assert(!(t0 != t0));

			assert(t1 == t0);
			assert(!(t1 != t0));
		}

		static void TestTransformToTransformOperators()
		{
			const Transform
				t0(Vector3(1, 2, 3), Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI_2)),
				t1(Vector3(1, 2, 3), Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI_2));

			assert(near(t1 * t0, Transform(Vector3(2, 4, 6), Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI))));
		}

		static void TestTransformToVectorOperators()
		{
			const Transform t0(Vector3(1, 2, 3), Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI_2));
			const Vector3 v0(1, 0, 0);

			assert(t0 * v0 == Vector3(1, 2, 2));
		}

		static void TestAffectationOperators()
		{
			const Transform t0(Vector3(1, 2, 3), Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI_2));
			Transform t1(Vector3(1, 2, 3), Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI_2));

			assert(near((t1 *= t0), Transform(Vector3(2, 4, 6), Quaternion::AxisAngle(Vector3(0, 1, 0), M_PI))));
		}

		static void TestInverse()
		{
			const Transform
				t0,
				t1(Vector3(1, 2, 3), Quaternion::AxisAngle(Vector3(1, 1, 1), M_PI_2));

			assert(t0.Inverse() == t0);
			assert(near(t1.Inverse(), Transform(Vector3(-1, -2, -3), Quaternion::AxisAngle(Vector3(1, 1, 1), -M_PI_2))) && t1.Inverse() * t1 == Transform::identity);
		}
	};
}

int main(int argc, char* argv[])
{
	using namespace TooGoodEngine;
	TestTransform::TestConstructor();
	TestTransform::TestComparison();
	TestTransform::TestTransformToTransformOperators();
	TestTransform::TestTransformToVectorOperators();
	TestTransform::TestAffectationOperators();
	TestTransform::TestInverse();
	return EXIT_SUCCESS;
}