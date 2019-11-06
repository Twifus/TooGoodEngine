#pragma once

#include "Vector3.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
	class ParticleContact
	{
	private:
		double restitution;
		double interpenetration;
		Vector3 contactNormal;
		// The 2 elements
		Particle* particleA;
		Particle* particleB;
		// if B is a plane, set to 1 else 0
		int isBplane;

        // Sub functions to compute contact resolution
        void ResolveVelocity();
        void ResolvePenetration();

	public:
		ParticleContact(Particle* a, Particle* b, double restitution);
		ParticleContact(Particle* p, Vector3 planPoint, Vector3 planNormal, double restitution);
        // Compute approach velocity value
        double ApproachVelocity() const;
        // Resolve contact (penetration and impulsion)
		void Resolve();
	};
}