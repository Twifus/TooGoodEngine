#pragma once

#include "Vector3.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
    // Class used to resolve a contact between 2 particles,
    // or between 1 particle and the floor
	class ParticleContact
	{
	private:
		Particle* particles[2];
		float restitution; // elasticity coeficient
		float interpenetration; // distance
		Vector3 contactNormal;

        // Sub functions to compute contact resolution
        void ResolveVelocity(double time);
        void ResolvePenetration();

	public:
        ParticleContact(Particle* a, float restitution);
		ParticleContact(Particle* a, Particle* b, float restitution);

        // Compute approch velocity value
        double ApprochVelocity() const;
        // Resolve contact (penetration and impulsion)
		void Resolve(double time);
	};
}