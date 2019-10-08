#include <iostream>
#include <SDL.h>
#include <vector>
#include <tuple>

#include "Vector3.hpp"
#include "Particle.hpp"
#include "Frame.hpp"
#include "Sprite.hpp"
#include "GameSDL.hpp"

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

	gameSDL.CreateSprite(&stone,  "../sprites/red_circle.png");
	gameSDL.CreateSprite(&bullet, "../sprites/white_circle.png");
	gameSDL.CreateSprite(&rocket, "../sprites/green_circle.png");
}


int main (int argc, char* argv[])
{
	initParticles();

	Frame f = Frame();
	
	////////////////
	// EVENT LOOP //
	while (1)
	{
		// Mesure deltaTime since last frame
		f.computeDeltaFrame();
		
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