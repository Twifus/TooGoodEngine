#pragma once
#include "Particle.hpp"

namespace TooGoodEngine
{
	class ParticleForceGenerator
	{
	public:
		virtual ~ParticleForceGenerator() = default;
		virtual void UpdateForce(Particle &particle, double time) const = 0;
	};
}

