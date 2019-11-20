#include <vector>
#include <iostream>

#include "Frame.hpp"
#include "BoxRigidBody.hpp"

using namespace TooGoodEngine;

// boite qui se collide
// boite qui tourne

std::vector<BoxRigidBody> objects;

// Crée les boites de test
void CreateBody()
{
    // Voiture 1 vers la droite (sur l'axe x)
    BoxRigidBody car1(10, 4, 2, 2);
    car1.position = Vector3::zero;
    // Force vers la droite au centre de masse
    car1.AddForceAtBodyPoint(Vector3(5,0,0), Vector3::zero);
    objects.push_back(car1);

    // Voiture 2 vers la gauche (sur l'axe x)
    BoxRigidBody car2(10, 4,2,2);
    car2.position = Vector3::right * 10;
    car2.orientation = Quaternion(0,0,1,0); // 180 degree autour de y
    // Force vers la gauche au centre de masse
    car2.AddForceAtBodyPoint(Vector3(-5,0,0), Vector3::zero);
    objects.push_back(car2);

    // Cube en l'air (en haut à droite dans le plan xy)
    BoxRigidBody fly(2, 2,2,2);
    fly.position = 10 * (Vector3::up + Vector3::right);
    // Forces pour le faire tourner sur place
    fly.AddForceAtBodyPoint(Vector3(0, 5,0), Vector3( 1, 1,0));
    // fly.AddForceAtBodyPoint(Vector3(0,-5,0), Vector3(-1,-1,0));
    objects.push_back(fly);

    // objects = {car1, car2, fly};

}

// Affichage des objets
void Display(const RigidBody &body, const char* name)
{
    Vector3 corner_pos = body.BodyToWorld(Vector3(1,1,1));
    std::cout << name;
    std::cout << " :  center" << body.position;
    std::cout << " \t corner" << corner_pos;
    std::cout << std::endl;
}


// Main
int main ()
{
    bool no_stop = true;
    double time = 0;
    double display_time = 0;

    CreateBody();

    Frame f = Frame();

    // Boucle de jeu
    while (no_stop)
    {
        f.computeDeltaFrame();

        // Maj de tous les objets
        for (auto &i : objects)
        {
            i.Update(f.getDeltaFrame());
            i.ClearAccumulation();
        }

        // Affichage toute les 1/2 seconde
        display_time += f.getDeltaFrame();
        if (display_time >= 0.5)
        {
            Display(objects[0], "car1");
            Display(objects[1], "car2");
            Display(objects[2], "fly");
            std::cout << std::endl;
            display_time = 0;
        }

        time += f.getDeltaFrame();
        if (time > 5)
            no_stop = false;

    }
    
    return 0;
}