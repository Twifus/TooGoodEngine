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
    BoxRigidBody car1(10, 20, 10, 10);
    car1.position = Vector3::zero;
    // Force vers la droite au centre de masse
    car1.AddForceAtBodyPoint(Vector3(5,0,0), Vector3::zero);
    // objects.push_back(car1);

    // Voiture 2 vers la gauche (sur l'axe x)
    BoxRigidBody car2(10, 20,10,10);
    car2.position = Vector3::right * 100;
    car2.orientation = Quaternion(0,0,1,0); // 180 degree autour de y
    // Force vers la gauche au centre de masse
    car2.AddForceAtBodyPoint(Vector3(-5,0,0), Vector3::zero);
    // objects.push_back(car2);

    // Cube en l'air (en haut à droite dans le plan xy)
    BoxRigidBody fly(2, 10,10,10);
    fly.position = 100 * (Vector3::up + Vector3::right);
    // Forces pour le faire tourner sur place
    fly.AddForceAtBodyPoint(Vector3(0, 2,0), Vector3( 5,0,0));
    fly.AddForceAtBodyPoint(Vector3(0,-2,0), Vector3(-5,0,0));
    // objects.push_back(fly);

    objects = {car1, car2, fly};

}

// Affichage des objets
void Display(const RigidBody &body, const char* name)
{
    Vector3 corner_pos = body.BodyToWorld(Vector3(10,10,10));
    std::cout << name;
    std::cout << " :  center" << body.position;
    std::cout << "  corner" << corner_pos;
    std::cout << std::endl;
}


// Main
int main ()
{
    Frame f = Frame();

    // Boucle de jeu
    while (1)
    {
        f.computeDeltaFrame();
        // Maj de tous les objets
        for (auto &i : objects)
        {
            i.Update(f.getDeltaFrame());
            i.ClearAccumulation();
        }
        // Affichage
        Display(objects[0], "car1");
        Display(objects[1], "car2");
        Display(objects[2], "car3");
        std::cout << std::endl;
    }
    
    return 0;
}