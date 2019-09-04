#pragma once

#include "Vector3.hpp"

namespace TooGoodEngine
{
    class Particule
    {
    private:
        double masse;
        double inverseMasse;
        double dumping;

    public:
        Vector3 position;
        Vector3 velocite;
        Vector3 acceleration;

        Particule();
        Particule(double m);
        Particule(double m, Vector3 pos);

        double InverseMasse() const;
        void SetMasse(double m);
        double GetMasse() const;
        void SetDumping(double d);

        void Integrer(double temps);
    };
}