#pragma once

#include "Vector3.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
	class ParticleContact
	{
	private:
		float restitution;
		float interpenetration;
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
		ParticleContact(Particle* a, Particle* b, float restitution);
		ParticleContact(Particle* p, Vector3 planPoint, Vector3 planNormal, float restitution);
        // Compute approch velocity value
        double ApprochVelocity() const;
        // Resolve contact (penetration and impulsion)
		void Resolve();
	};
}