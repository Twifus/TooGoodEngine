#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class SpringForceGenerator : public ParticleForceGenerator
	{
	private:
		Particle& extremeParticle;
		double k;
		double length;

	public:
		SpringForceGenerator(Particle& particle, double k, double length);
		void UpdateForce(Particle& particle, double time) const;
	};
}