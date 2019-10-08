#pragma once

#include "Particle.hpp"
#include "ParticleForceGenerator.hpp"

namespace TooGoodEngine
{
	class DragForceGenerator : ParticleForceGenerator
	{
	private:
		double k1, k2;

	public:
		DragForceGenerator(double k1, double k2);
		void UpdateForce(Particle& particle, double time) const;
	};
}