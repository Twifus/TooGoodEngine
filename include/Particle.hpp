#pragma once

#include "Vector3.hpp"

namespace TooGoodEngine
{
    class Particle
    {
    private:
        double mass;
        double inverseMass;
        double damping;

		double radius;

		Vector3 velocity;
		Vector3 acceleration;

		Vector3 resultantForce;

    public:
		Vector3 position;

		// Default constructor
        Particle();

		// Overloaded constructor for a full initialization
        Particle(
			double mass, double radius = 1,
			Vector3 position = Vector3::zero,
			Vector3 velocity = Vector3::zero,
			double damping = 0.95
		);

		// Mass accessors
		void SetMass(double m);
		double GetMass() const;
		// Radius getter
		double GetRadius() const;
		// Velocity getter
		Vector3 GetVelocity() const;

		// Easy way to get 1/m (save calculation time)
        double GetInverseMass() const;

		// Add a force to the resultant force buffer
		void AddForce(Vector3 newForce);

		// Make an impulsion on the velocity (result of a collision)
		void Impulsion(Vector3 newImpulsion);

		// Clear the resultant force
		void ClearForces();
        
		// Updating physics of the particle (position, velocity, acceleration according time spend)
        void Update(double time);
    };
}