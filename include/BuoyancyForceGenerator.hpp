#pragma once

#include "Particle.hpp"
#include "ParticleForceGenerator.hpp"

namespace TooGoodEngine
{
	class BuoyancyForceGenerator : public ParticleForceGenerator
	{
	private:
		double maxDepth, volume, liquidHeight, density;

	public:
		BuoyancyForceGenerator(double maxDepth, double volume, double liquidHeight, double density);
		virtual void UpdateForce(Particle& particle, double time) const;
	};
}