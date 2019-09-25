#include "BungeeSpringForceGenerator.hpp"

namespace TooGoodEngine
{

	void BungeeSpringForceGenerator::BungeeSpringForceGenerator(Particle &particle, double k, double length) :
		extremeParticle(particle), k(k), length(length) {}

	void BungeeSpringForceGenerator::UpdateForce(Particle &particle, float time)
	{
		double appliedLength = (particle.GetPosition() - extremeParticle.GetPosition()).Magnitude();
		if (appliedLength > length)
			particle.AddForce(-k * (appliedLength - length));
	}
}