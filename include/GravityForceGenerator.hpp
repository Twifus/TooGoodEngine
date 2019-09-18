#pragma once
#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class GravityForceGenerator(ParticleForceGenerator)
	{
	public:
		Vector3 gravity;

		GravityForceGenerator();
		void UpdateForce(Particle &particle, float time);
	};
}

