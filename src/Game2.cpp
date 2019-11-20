#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>

#include "Frame.hpp"
#include "BoxRigidBody.hpp"

using namespace TooGoodEngine;

std::vector<BoxRigidBody> objects;
bool impact = false;

// Crée les boites de test
void CreateBody()
{
    // Voiture 1 vers la droite (sur l'axe x)
    BoxRigidBody car1(10, 4, 2, 2);
    car1.SetPosition(Vector3::zero);
    objects.push_back(car1);

    // Voiture 2 vers la gauche (sur l'axe x)
    BoxRigidBody car2(10, 4,2,2);
    car2.SetPosition(Vector3::right * 10);
    car2.SetOrientation(Quaternion::AxisAngle(Vector3::up, M_PI)); // 180 degree autour de y
    objects.push_back(car2);
	
    // Cube en l'air (en haut à droite dans le plan xy)
    BoxRigidBody fly(2, 2,2,2);
    fly.SetPosition(10 * (Vector3::right + Vector3::up));
    objects.push_back(fly);
}

void AddForces()
{
	// Force vers l'avant (en coordonnées locales) appliquée au centre de masse
	objects[0].AddForceAtBodyPoint(Vector3(5, 0, 0), Vector3::zero);

	// Force vers l'avant (en coordonnées locales) appliquée au centre de masse
	objects[1].AddForceAtBodyPoint(Vector3(5, 0, 0), Vector3::zero);

	if (!impact && std::abs(objects[0].GetPosition().x - objects[1].GetPosition().x) < 4)
	{
		std::cout << "==================\n===== IMPACT =====\n==================" << std::endl;
		impact = true;
		objects[1].AddForceAtBodyPoint(Vector3(-1000000, 0, 0), Vector3(2, 1, 1));
	}

	// Forces opposées en coordonnées locales pour faire tourner l'objet sur lui même sur place
	objects[2].AddForceAtBodyPoint(Vector3(0, 1, 0), Vector3(1, 0, 0));
	objects[2].AddForceAtBodyPoint(Vector3(0, -1, 0), Vector3(-1, 0, 0));
}

// Affichage des objets
void Display(const RigidBody &body, const char* name)
{
    Vector3 corner_pos = body.BodyToWorld(Vector3(1,1,1));
	std::cout << "[ " << name << " ]" << std::endl;
    std::cout << "center" << body.GetPosition() << "\t\tcorner" << corner_pos << std::endl;
    std::cout << "vitesse lin." << body.GetVelocity() << "\t\tvitesse ang." << body.GetAngularVelocity() << std::endl;
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
    while (true)
    {
        AddForces();

        f.computeDeltaFrame();

        // Maj de tous les objets
        for (auto &i : objects)
        {
            i.Update(f.getDeltaFrame());
            i.ClearAccumulation();
        }

        // Affichage toute les 1/2 seconde
        display_time += f.getDeltaFrame();
        if (display_time >= 0.1)
        {
			std::cout << "=====" << std::endl;
            Display(objects[0], "Car 1");
			std::cout << "---" << std::endl;
			Display(objects[1], "Car 2");
			std::cout << "----" << std::endl;
            Display(objects[2], "Flying cube");
            std::cout << std::endl;
            display_time = 0;
        }

        time += f.getDeltaFrame();
    }
    
    return 0;
}