#include "BungeeSpringForceGenerator.hpp"

namespace TooGoodEngine
{

	BungeeSpringForceGenerator::BungeeSpringForceGenerator(Particle &particle, double k, double length) :
		extremeParticle(particle), k(k), length(length) {}

	void BungeeSpringForceGenerator::UpdateForce(Particle &particle, double time) const
	{
		Vector3 direction = (particle.GetPosition() - extremeParticle.GetPosition());
		double appliedLength = direction.Magnitude();
		if (appliedLength > length)
			particle.AddForce(-k * (appliedLength - length) * direction.Normalized());
	}
}