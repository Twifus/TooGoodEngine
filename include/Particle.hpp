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

		// Constructeur par d�faut
        Particle();
		// Surcharge du constructeur pour la masse (et potentiellement le frottement)
		Particle(double mass, double damping = 0.95);
		// Surcharge du constructeur pour un initialisation compl�te
        Particle(
			double mass,
			Vector3 position = Vector3(),
			Vector3 velocity = Vector3(),
			Vector3 acceleration = Vector3(),
			double damping = 0.95
		);

		// Accesseurs pour la masse
		void SetMass(double m);
		double GetMass() const;

		// Permet d'obtenir directement la valeur de 1/m
        double InverseMasse() const;
        
		// Mise-�-jour des vecteurs pos/vel/acc en fonction du temps
        void Update(double temps);
    };
}