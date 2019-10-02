#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class GravityForceGenerator : ParticleForceGenerator
	{
	private:
		static Vector3 gravity;

	public:
		GravityForceGenerator() = default;
		void UpdateForce(Particle &particle, double time) const;
	};
}

