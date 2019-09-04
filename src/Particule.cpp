#include "Particule.hpp"

#include <cmath>
#include <limits>
static double double_max = std::numeric_limits<double>::max();

static double g = 10;

namespace TooGoodEngine
{
    Particule::Particule() :
    dumping(1), masse(1), inverseMasse(1) {}

    Particule::Particule(double d, double m) :
    dumping(d), masse(m), inverseMasse(1/masse) {}

    double Particule::InverseMasse() const
    {
        return inverseMasse;
    }

    void Particule::SetMasse(double m)
    {
        if (m<=0)
        {
            inverseMasse = double_max;
            masse = 1/double_max;
        }
        else
        {
            masse = m;
            inverseMasse = 1/m;
        } 
    }

    double Particule::GetMasse() const
    {
        return masse;
    }

    void Particule::Integrer(double temps)
    {
        //update position
        position = position + velocite * temps;
        // update vélocité
        velocite = velocite * std::pow(dumping, temps) + acceleration * temps;
        // update acceleration (constant pour l'instant ?)
        acceleration = acceleration + inverseMasse * Vector3(0, -g, 0);
    }
}

// using namespace TooGoodEngine;
// 
// // Exemples de particules
// int main()
// {
//     // Une pierre de 3 kilos qui tombe
//     Particule pierre(0.7, 3);
//     pierre.position = Vector3(0,100,0);

//     // Une balle tirée droite (faible résistance à l'air)
//     Particule balle(0.5, 0.5);
//     balle.velocite = Vector3(500, 0, 0);

//     // Une roquette avec propulseur tirée en diagonale haute (forte résistance à l'air)
//     Particule roquette(1, 5);
//     roquette.acceleration = Vector3(100, 100, 0);

//     return 0;
// }
