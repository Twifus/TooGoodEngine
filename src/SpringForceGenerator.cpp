#include "SpringForceGenerator.hpp"

namespace TooGoodEngine
{
	SpringForceGenerator::SpringForceGenerator(Particle &particle, double k, double length) : 
		extremeParticle(particle), k(k), length(length) {}

	void SpringForceGenerator::UpdateForce(Particle &particle, double time) const
	{
		Vector3 direction = (particle.GetPosition() - extremeParticle.GetPosition());
		particle.AddForce(-k * (direction.Magnitude() - length) * direction.Normalized());
	}
}
