#include "AnchoredSpringForceGenerator.hpp"

namespace TooGoodEngine
{

	AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector3 &point, double k, double length) :
		anchoredPoint(point), k(k), length(length) {}

	void AnchoredSpringForceGenerator::UpdateForce(Particle &particle, double time) const
	{
		Vector3 direction = (particle.GetPosition() - anchoredPoint);
		particle.AddForce(-k * (direction.Magnitude() - length) * direction.Normalized());
	}
}