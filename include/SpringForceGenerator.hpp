#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class SpringForceGenerator(ParticleForceGenerator)
	{
	public:
		Particle &extremeParticle;
		double k;
		double length;

		SpringForceGenerator(Particle &particle, double k, double length);
		void UpdateForce(Particle &particle, float time);
	};
}