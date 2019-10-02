#include "GravityForceGenerator.hpp"

namespace TooGoodEngine
{
	Vector3 GravityForceGenerator::gravity(0, -10, 0);

	void GravityForceGenerator::UpdateForce(Particle &particle, double time) const
	{
		if (particle.GetMass() != 0)
		{
			particle.AddForce(particle.GetMass() * gravity);
		}
	}
}
