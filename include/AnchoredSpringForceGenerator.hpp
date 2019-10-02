#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class AnchoredSpringForceGenerator : ParticleForceGenerator
	{
	private:
		Vector3 &anchoredPoint;
		double k;
		double length;

	public:
		AnchoredSpringForceGenerator(Vector3 &point, double k, double length);
		void UpdateForce(Particle &particle, double time) const;
	};
}