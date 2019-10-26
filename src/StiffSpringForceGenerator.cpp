#include "StiffSpringForceGenerator.hpp"
#include <iostream>

namespace TooGoodEngine
{
	StiffSpringForceGenerator::StiffSpringForceGenerator(Vector3 anchor, double k, double damping) :
		anchor(anchor), k(k), damping(damping) {}

	void StiffSpringForceGenerator::UpdateForce(Particle &particle, double time) const
	{
		Vector3 position = (particle.position - anchor);
		Vector3 direction = position.Normalized();
		Vector3 projectedVelocity = (particle.GetVelocity()).Dot(direction) * direction;
		particle.AddForce(-k * position - damping * projectedVelocity);
	}
}
