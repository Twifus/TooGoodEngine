#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class BungeeSpringForceGenerator(ParticleForceGenerator)
	{
	public:
		Particle &extremeParticle;
		double k;
		double length;

		BungeeSpringForceGenerator(Particle &particle, double k, double length);
		void UpdateForce(Particle &particle, float time);
	};
}