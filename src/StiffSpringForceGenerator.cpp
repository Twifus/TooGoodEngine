#include "StiffSpringForceGenerator.hpp"

namespace TooGoodEngine
{
	StiffSpringForceGenerator::StiffSpringForceGenerator(Vector3& anchor, double k, double damping) :
		anchor(anchor), k(k), damping(damping) {}

	void StiffSpringForceGenerator::UpdateForce(Particle &particle, double time) const
	{
		Vector3 position = (particle.GetPosition() - anchor);
		Vector3 direction = position.Normalized();
		Vector3 projectedVelocity = std::abs(Vector3::Dot(particle.GetVelocity(), direction)) * direction;
		particle.AddForce(-k * position - damping * projectedVelocity);
	}
}
