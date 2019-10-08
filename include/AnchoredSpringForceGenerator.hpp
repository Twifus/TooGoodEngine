#pragma once

#include "Particle.hpp"
#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class AnchoredSpringForceGenerator : ParticleForceGenerator
	{
	private:
		Vector3 anchor;
		double k;
		double length;

	public:
		AnchoredSpringForceGenerator(Vector3& point, double k, double length);
		void UpdateForce(Particle &particle, double time) const;
	};
}