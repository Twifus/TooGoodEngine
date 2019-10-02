#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class BungeeSpringForceGenerator : ParticleForceGenerator
	{
	private:
		Particle &extremeParticle;
		double k;
		double length;

	public:
		BungeeSpringForceGenerator(Particle &particle, double k, double length);
		void UpdateForce(Particle &particle, double time) const;
	};
}