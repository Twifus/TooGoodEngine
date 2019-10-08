#include "Particle.hpp"

#include <iostream>
#include <cmath>
#include <limits>
static double double_max = std::numeric_limits<double>::max();

static double g = 10;

namespace TooGoodEngine
{
    Particle::Particle() : Particle(1) {}

	Particle::Particle(double m, double d) : Particle(m, Vector3(), Vector3(), d) {}

    Particle::Particle(double m, Vector3 p, Vector3 v, double d) : damping(d), position(p), velocity(v)
	{
		SetMass(m);
	}

	Vector3 Particle::GetPosition() const
	{
		return position;
	}

	Vector3 Particle::GetVelocity() const
	{
		return velocity;
	}

	double Particle::GetInverseMass() const
    {
        return inverseMass;
    }

    void Particle::SetMass(double m)
    {
        if (m<=0)
        {
            inverseMass = double_max;
            mass = 1/double_max;
        }
        else
        {
            mass = m;
            inverseMass = 1/m;
        } 
    }

    double Particle::GetMass() const
    {
        return mass;
    }

	void Particle::AddForce(Vector3 newForce)
	{
		resultantForce += newForce;
	}

    void Particle::Impulsion(Vector3 newImpulsion)
    {
        velocity += inverseMass * newImpulsion;
    }

	void Particle::ClearForces()
	{
		resultantForce = Vector3(0, 0, 0);
	}

    void Particle::Update(double time)
    {
        //update position
        position = position + velocity * time;
        // update velocity
        velocity = velocity * std::pow(damping, time) + acceleration * time;
        // update acceleration (no forces yet, except gravity...)
        acceleration = Vector3(0, -g, 0);
    }
}

