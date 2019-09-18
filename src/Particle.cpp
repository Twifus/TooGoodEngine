#include "Particle.hpp"

#include <iostream>
#include <cmath>
#include <limits>
static double double_max = std::numeric_limits<double>::max();

static double g = 10;

namespace TooGoodEngine
{
    Particle::Particle() :
    mass(1), inverseMass(1), damping(0.95) {}

	Particle::Particle(double m, double d) :
		mass(m), inverseMass(1 / mass), damping(d) {}

    Particle::Particle(double m,
		Vector3 p,
		Vector3 v,
		Vector3 a,
		double d) :
	mass(m), inverseMass(1/mass), damping(d),
	position(p), velocity(v), acceleration(a) {}

	Vector3 Particle::GetPosition() const
	{
		return position;
	}

	Vector3 Particle::GetVelocity() const
	{
		return velocity;
	}

	double Particle::InverseMasse() const
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

