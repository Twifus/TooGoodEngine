#pragma once
#include "Particle.hpp"

class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle * particle, float time) = 0;
};
