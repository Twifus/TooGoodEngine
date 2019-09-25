#include <iostream>
#include <SDL.h>
#include <vector>
#include <tuple>

#include "Vector3.hpp"
#include "Particle.hpp"
#include "Frame.hpp"
#include "Sprite.hpp"

using namespace TooGoodEngine;

std::vector<Particle> particules;
std::vector<Sprite> sprites;

// SDL_Rect r;
SDL_Event event;
SDL_Window* window = NULL;

void initParticles()
{
	Particle stone = Particle(1, Vector3(0, 7, 0));
	Particle bullet = Particle(3, Vector3(0, 5, 0), Vector3(10, 0, 0));
	Particle rocket = Particle(5, Vector3(0, 0, 0), Vector3(10, 15, 0));

	particules = { stone, bullet, rocket };

	int colors[][3] = {{255,0,0}, {0,255,0}, {0,0,255}};

	for (int i=0; i < particules.size(); i++)
	{
		sprites.push_back(Sprite(&particules[i], colors[i][0], colors[i][1], colors[i][2]));
	}

}

SDL_Renderer* initRenderer()
{
	// Create a sdl window
	window = SDL_CreateWindow("Simulation de tir", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	if (!window)
		return nullptr;

	// Create a renderer
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
		return nullptr;

	// Set background to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

//	r.w = BOX_SIZE;
//	r.h = BOX_SIZE;
	
	return renderer;
}


int main (int argc, char* argv[])
{
	initParticles();
	SDL_Renderer* renderer = initRenderer();
	if (renderer == nullptr)
		return EXIT_FAILURE;

	Frame f = Frame();
	
	////////////////
	// EVENT LOOP //
	while (1)
	{
		// Mesure deltaTime since last frame
		f.computeDeltaFrame();

		// Event management
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}

		// Clear renderer before drawing the new frame
		SDL_RenderClear(renderer);

		DrawAxes(renderer);
		
		// Update each particle position
		for (auto &i : particules)
		{
			i.Update(f.getDeltaFrame());
		}

		//Loop for particles display
		for (auto &i : sprites)
		{
			i.Draw(renderer);
		}

    	SDL_RenderPresent(renderer);
	}
	// EVENT LOOP //
	////////////////


    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}