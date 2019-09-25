#include "SpringForceGenerator.hpp"

namespace TooGoodEngine
{

	void SpringForceGenerator::SpringForceGenerator(Particle &particle, double k, double length) : 
		extremeParticle(particle), k(k), length(length) {}

	void SpringForceGenerator::UpdateForce(Particle &particle, float time)
	{
		particle.AddForce(-k * (particle.GetPosition() - extremeParticle.GetPosition()).Magnitude() - length));
	}
}