#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <tuple>
#include <vector>

#include "Frame.hpp"
#include "GameSDL.hpp"
#include "Particle.hpp"
#include "ParticleContact.hpp"
#include "ParticleContactResolver.hpp"
#include "Vector3.hpp"
#include "Sprite.hpp"

using namespace TooGoodEngine;

std::vector<Particle> particules;
std::vector<Sprite> sprites;

GameSDL gameSDL = GameSDL();


void initParticles()
{
	Particle stone = Particle(1, 3, Vector3(0, 7, 0));
	Particle bullet = Particle(3, 1, Vector3(0, 5, 0), Vector3(10, 0, 0));
	Particle rocket = Particle(5, 2, Vector3(0, 0, 0), Vector3(10, 15, 0));

	particules = { stone, bullet, rocket };

	gameSDL.CreateSprite(&stone,  "red_circle.png");
	gameSDL.CreateSprite(&bullet, "white_circle.png");
	gameSDL.CreateSprite(&rocket, "green_circle.png");
}


int main (int argc, char* argv[])
{
	initParticles();

	Frame f = Frame();
	ParticleContactResolver contactResolver;
	
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

		// Update each particle position
		for (auto &i : particules)
		{
			i.Update(f.getDeltaFrame());
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