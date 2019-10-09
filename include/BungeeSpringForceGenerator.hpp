#pragma once

#include "Particle.hpp"
#include "ParticleForceGenerator.hpp"

namespace TooGoodEngine
{
	class BungeeSpringForceGenerator : public ParticleForceGenerator
	{
	private:
		Particle& extremeParticle;
		double k;
		double length;

	public:
		BungeeSpringForceGenerator(Particle& particle, double k, double length);
		void UpdateForce(Particle &particle, double time) const;
	};
}