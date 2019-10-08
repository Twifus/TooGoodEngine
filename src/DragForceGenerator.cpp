#include "DragForceGenerator.hpp"

namespace TooGoodEngine
{
	DragForceGenerator::DragForceGenerator(double k1, double k2) : k1(k1), k2(k2) {}

	void DragForceGenerator::UpdateForce(Particle& particle, double time) const
	{
		particle.AddForce(-(k1 * particle.GetVelocity().Magnitude() + k2 * particle.GetVelocity().SquaredMagnitude()) * particle.GetVelocity().Normalized());
	}
}
