#define _USE_MATH_DEFINES
#include <cmath>

#include "RigidBody.hpp"
#include <cassert>
#include <stdexcept>


namespace TooGoodEngine
{
	class TestRigidBody
	{
	public:
		static void TestBaseChange()
		{
			RigidBody
				rb0(1),
				rb1(1);

			rb0.SetOrientation(Quaternion::AxisAngle(Vector3::up, M_PI_2));
			rb1.SetOrientation(Quaternion::AxisAngle(Vector3::forward, M_PI_2));
			
			{
				Vector3 v0 = rb0.GetOrientation().Inverse() * Vector3(1, 1, 1);
				Vector3 v1 = rb0.GetOrientation() * Vector3(1, 1, 1);

				Vector3 v2 = rb1.GetOrientation().Inverse() * Vector3(1, 1, 1);
				Vector3 v3 = rb1.GetOrientation() * Vector3(1, 1, 1);
			}

			{
				Vector3 v0 = rb0.WorldToBody(Vector3(1, 1, 1));
				Vector3 v1 = rb0.BodyToWorld(Vector3(1, 1, 1));

				Vector3 v2 = rb1.WorldToBody(Vector3(1, 1, 1));
				Vector3 v3 = rb1.BodyToWorld(Vector3(1, 1, 1));
			}
		}
	};
}

int main(int argc, char* argv[])
{
	using namespace TooGoodEngine;
	TestRigidBody::TestBaseChange();
	return EXIT_SUCCESS;
}