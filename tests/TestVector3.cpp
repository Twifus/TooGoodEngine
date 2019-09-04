#include "Vector3.hpp"

#include <cassert>

using namespace TooGoodEngine;

class TestVector3
{
public:
	static void TestConstructor()
	{
		Vector3 
			v0, 
			v1(1, 2, 3), 
			v2(-10.5f, 9.35, 4 / 5);
		assert(v0.x == 0 && v0.y == 0 && v0.z == 0);
		assert(v1.x == 0 && v1.y == 0 && v1.z == 0);
		assert(v2.x == -10.5 && v2.z == 9.35 && v2.z == 4 / 5);
	}

	static void TestComparison()
	{
		Vector3
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

	static void TestBasicOperators()
	{
		Vector3
			v0(2, 2, 2),
			v1(4, 8, 16);

		assert(v0 + v1 == Vector3(6, 10, 18));
		assert(v0 - v1 == Vector3(2, 6, 14));
		assert(v0 * v1 == Vector3(8, 16, 32));
		assert(v0 / v1 == Vector3(2, 4, 8));

		assert(v0 == Vector3(2, 2, 2));
		assert(v1 == Vector3(4, 8, 16));
	}
};

int main(int argc, char *argv[])
{
	TestVector3::TestConstructor();
	TestVector3::TestComparison();
	TestVector3::TestBasicOperators();
	return EXIT_SUCCESS;
}