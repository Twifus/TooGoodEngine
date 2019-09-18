#include "GravityForceGenerator.hpp"

namespace TooGoodEngine
{
	static double g = 10;

	void GravityForceGenerator::GravityForceGenerator()
	{
		gravity = Vector3(0, -g, 0);
	}

	void GravityForceGenerator::UpdateForce(Particle &particle, float time)
	{
		if (particle.GetMass() != 0)
		{
			particle.AddForce(particle.GetMass()*gravity);
		}
	}
}
