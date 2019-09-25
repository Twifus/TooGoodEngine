#include "AnchoredSpringForceGenerator.hpp"

namespace TooGoodEngine
{

	void AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector3 &point, double k, double length) :
		anchoredPoint(point), k(k), length(length) {}

	void AnchoredSpringForceGenerator::UpdateForce(Particle &particle, float time)
	{
		particle.AddForce(-k * (particle.GetPosition() - anchoredPoint.GetPosition()).Magnitude() - length));
	}
}