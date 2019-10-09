#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <tuple>
#include <vector>

#include "Frame.hpp"
#include "ForcesRegistery.hpp"
#include "GameSDL.hpp"
#include "Particle.hpp"
#include "ParticleContact.hpp"
#include "ParticleContactResolver.hpp"
#include "ParticleForceGenerator.hpp"
#include "GravityForceGenerator.hpp"
#include "Vector3.hpp"
#include "Sprite.hpp"

using namespace TooGoodEngine;

std::vector<Particle> particules;
std::vector<Sprite> sprites;

GameSDL gameSDL = GameSDL();


void initParticles()
{
	Particle stone = Particle(1, 0.1, Vector3(-3, 0, 0), Vector3(10, 5, 0));
	Particle bullet = Particle(3, 0.3, Vector3(0, 0, 0), Vector3( 0, 5, 0));
	Particle rocket = Particle(5, 0.5, Vector3(3, 0, 0), Vector3( 0, 5, 0));

	particules = { stone, bullet, rocket };

	gameSDL.CreateSprite(&particules[0], "sprites/red_circle.png");
	gameSDL.CreateSprite(&particules[1], "sprites/white_circle.png");
	gameSDL.CreateSprite(&particules[2], "sprites/green_circle.png");
}


int main (int argc, char* argv[])
{
	initParticles();

	Frame f = Frame();
	ParticleContactResolver contactResolver;
	ForcesRegistery registry;
	GravityForceGenerator gravityGenerator;

	////////////////
	// EVENT LOOP //
	while (1)
	{
		// Mesure deltaTime since last frame
		f.computeDeltaFrame();
		
		for (auto& p1 = particules.begin(); p1 < particules.end(); p1++)
		{
			for (auto& p2 = p1 + 1; p2 < particules.end(); p2++)
			{
				if ((p1->position - p2->position).Magnitude() <= std::min(p1->GetRadius(), p2->GetRadius()))
				{
					contactResolver.AddContact(ParticleContact(&(*p1), &(*p2), 0.95));
				}
			}
		}
		contactResolver.Resolve(f.getDeltaFrame());
		contactResolver.Clear();

		for (auto& i : particules)
		{
			registry.Add(i, gravityGenerator);
		}
		registry.UpdateForces(f.getDeltaFrame());
		registry.Clear();
		
		// Update each particle position
		for (auto &i : particules)
		{
			i.Update(f.getDeltaFrame());
			i.ClearForces();
		}
		
		int exit = gameSDL.HandleEvents();
		if (exit == -1)
			break;

		gameSDL.render();
	}
	// EVENT LOOP //
	////////////////

    return EXIT_SUCCESS;
}
