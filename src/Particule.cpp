#include "Particule.hpp"

#include <iostream>
#include <cmath>
#include <limits>
static double double_max = std::numeric_limits<double>::max();

static double g = 10;

namespace TooGoodEngine
{
    Particule::Particule() :
    masse(1), inverseMasse(1), damping(0.95) {}

    Particule::Particule(double d, double m) :
    masse(m), inverseMasse(1/masse), damping(d) {}

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
        velocite = velocite * std::pow(damping, temps) + acceleration * temps;
        // update acceleration (constant pour l'instant ?)
        acceleration = Vector3(0, -g, 0);
    }
}

// using namespace TooGoodEngine;

// // Exemples de particules
// int main()
// {
//     // Une pierre de 3 kilos qui tombe
//     Particule pierre(0.7, 3);
//     pierre.position = Vector3(0,100,0);

//     // Une balle tirée droite (faible résistance à l'air)
//     Particule balle(0.95, 0.5);
//     balle.velocite = Vector3(100, 0, 0);

//     // Une roquette avec propulseur tirée en diagonale haute (forte résistance à l'air)
//     Particule roquette(0.5, 5);
//     roquette.velocite = Vector3(20, 20, 0);

//     Particule parts[] = {pierre, balle, roquette};
//     const char * names[] = {"pierre", "balle", "roquette"};

//     double tps = 0.1;
//     bool stop = false;

//     while (!stop)
//     {
//         // std::cout << "tps : " << tps << std::endl;
//         int n = 0;
//         for (auto &i : parts)
//         {
//             i.Integrer(tps);
//             // std::cout << names[n] << " : " << i.position << std::endl;
//             std::cout << i.position.x << ", " << i.position.y << ", " << n << std::endl;
//             n += 1;
//         }
//         tps += 0.3;
       
//         // std::cout << std::endl;

//         if (tps > 4)
//         {
//             stop = true;
//         }
//     }

//     return 0;
// }
