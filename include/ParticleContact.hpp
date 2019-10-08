#pragma once

#include "Vector3.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
    class ParticleContact
    {
    private:
        Particle* particles[2];
        float restitution; // coef d'élasiticité
        float interpenetration; // distance d'interpenetration
        Vector3 contactNormal;

        void ResolveVelocity(double time);
        void ResolvePenetration(double time);

    public:
        ParticleContact();
        ~ParticleContact();

        double ApprochVelocity();

        void Resolve(double time);
    };
}