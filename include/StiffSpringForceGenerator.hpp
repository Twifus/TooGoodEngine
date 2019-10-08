#pragma once

#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class StiffSpringForceGenerator : ParticleForceGenerator
	{
	private:
		Vector3& anchor;
		double k;
		double damping;

	public:
		StiffSpringForceGenerator(Vector3& anchor, double k, double damping);
		void UpdateForce(Particle& particle, double time) const;
	};
}