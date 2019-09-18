#pragma once
#include "Particle.hpp"

namespace TooGoodEngine
{
	class ParticleForceGenerator
	{
	public:
		virtual void UpdateForce(Particle &particle, float time) = 0;
	};
}

