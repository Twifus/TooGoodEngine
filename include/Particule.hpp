#pragma once

#include "Vector3.hpp"

namespace TooGoodEngine
{
    class Particule
    {
    private:
        double masse;
        double inverseMasse;
        double damping;

    public:
        Vector3 position;
        Vector3 velocite;
        Vector3 acceleration;

        Particule();
        Particule(double d, double m);

        double InverseMasse() const;
        void SetMasse(double m);
        double GetMasse() const;

        void Integrer(double temps);
    };
}