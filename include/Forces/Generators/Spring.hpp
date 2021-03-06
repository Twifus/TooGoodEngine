#pragma once

#include "Forces/IForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			class Spring : public IForceGenerator
			{
			private:
				Vector3 pos1;
				RigidBody& other;
				Vector3 pos2;
				double k;
				double length;

			public:
				Spring(RigidBody& other, double k, double length);
				Spring(const Vector3& pos1, RigidBody& other, const Vector3& pos2, double k, double length);
				void UpdateForce(RigidBody& rb, double time) const;
			};
		}
	}
}