#pragma once

#include "RigidBody.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		class IForceGenerator
		{
		public:
			virtual ~IForceGenerator() = default;
			virtual void UpdateForce(RigidBody& particle, double time) const = 0;
		};
	}
}

