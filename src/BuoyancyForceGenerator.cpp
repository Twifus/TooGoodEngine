#include "BuoyancyForceGenerator.hpp"

namespace TooGoodEngine
{
	BuoyancyForceGenerator::BuoyancyForceGenerator(double maxDepth, double volume, double liquidHeight, double density) : 
		maxDepth(maxDepth), volume(volume), liquidHeight(liquidHeight), density(density) {}

	void BuoyancyForceGenerator::UpdateForce(Particle& particle, double time) const
	{
		double d = (Vector3::Dot(particle.position, Vector3::up) - liquidHeight - maxDepth) / (2 * maxDepth);
		if (d <= 0)
			return;
		else if (d >= 1)
			particle.AddForce(volume * density * Vector3::up);
		else
			particle.AddForce(d * volume * density * Vector3::up);
	}
}