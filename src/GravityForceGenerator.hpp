#pragma once
#include "ParticleForceGenerator.hpp"
#include "Vector3.hpp"

class GravityForceGenerator(ParticleForceGenerator)
{
public:
	Vector3 gravity;

	GravityForceGenerator();
	void updateForce(Particle * particle, float time);
};
