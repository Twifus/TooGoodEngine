#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class AnchoredSpringForceGenerator(ParticleForceGenerator)
	{
	public:
		Vector3 &anchoredPoint;
		double k;
		double length;

		AnchoredSpringForceGenerator(Vector3 &point, double k, double length);
		void UpdateForce(Particle &particle, float time);
	};
}