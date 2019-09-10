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

        Particle();
        Particle(double damping, double mass);

        double InverseMasse() const;
        void SetMass(double m);
        double GetMass() const;

        void Update(double temps);
    };
}