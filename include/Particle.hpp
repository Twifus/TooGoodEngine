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

		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;

		Vector3 resultantForce;

    public:

		// Default constructor
        Particle();
        
		// Overloaded constructor to setup mass (and damping if needed)
		Particle(double mass, double damping = 0.95);

		// Overloaded constructor for a full initialisation
        Particle(
			double mass,
			Vector3 position = Vector3(),
			Vector3 velocity = Vector3(),
			Vector3 acceleration = Vector3(),
			double damping = 0.95
		);

		// Mass accesors
		void SetMass(double m);
		double GetMass() const;

		// Position, velocity and accel accessors
		Vector3 GetPosition() const;
		Vector3 GetVelocity() const;

		// Easy way to get 1/m (save calculation time)
        double InverseMasse() const;

		// Add a force to the resultant force buffer
		void AddForce(Vector3 newForce);
		// Clear the resultant force
		void ClearForces();
        
		// Updating physics of the particle (pos, vel, acc according time spend)
        void Update(double temps);
    };
}