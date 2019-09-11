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

    public:
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;

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

		// Easy way to get 1/m (save calculation time)
        double InverseMasse() const;
        
		// Updating physics of the particle (pos, vel, acc according time spend)
        void Update(double temps);
    };
}