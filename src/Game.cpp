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
	Particle stone = Particle(10, Vector3(0, 10, 0));
	Particle bullet = Particle(1, Vector3(0, 0, 0), Vector3(100, 0, 0));

	particules = { stone, bullet };

	for (auto &i : particules)
	{
		sprites.push_back(Sprite(&i));
	}

// This funtion draw white axes on the given renderer. It helps locating particles in the world space.
void DrawAxes(SDL_Renderer *renderer)
{
	SDL_Rect xaxis, yaxis;
	xaxis.w = VIEW_WIDTH - 2 * AXIS_OFFSET;
	xaxis.h = AXIS_WIDTH;
	xaxis.x = AXIS_OFFSET;
	xaxis.y = VIEW_HEIGHT - 2 * AXIS_OFFSET - AXIS_WIDTH;

	yaxis.w = AXIS_WIDTH;
	yaxis.h = VIEW_HEIGHT - 2 * AXIS_OFFSET;
	yaxis.x = 2 * AXIS_OFFSET;
	yaxis.y = AXIS_OFFSET;

	// Set color to blue (will change rect color)
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

	SDL_RenderFillRect( renderer, &xaxis );
	SDL_RenderFillRect( renderer, &yaxis );

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
}

int main (int argc, char* argv[])
{
	// Create a sdl window
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Simulation de tir", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	if (!window)
		return nullptr;

	// Create a renderer
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
		return nullptr;

	// Set background to black
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

	SDL_Rect r;
	r.w = BOX_SIZE;
	r.h = BOX_SIZE;
	SDL_Event event;
	
	// Particle init
	Frame f = Frame();
	std::vector<Particle> p = { Particle(), Particle(3, 0.7), Particle(5, 0.5) }; // Particle
	std::vector<Vector3> p0 = { Vector3(0, 7, 0), Vector3(0, 5, 0), Vector3() }; // Initial pos
	std::vector<Vector3> v = { Vector3(), Vector3(10, 0, 0), Vector3(10, 15, 0) }; // Initial velocity
	std::vector<std::tuple<int, int, int>> c = { std::make_tuple(255, 0, 0), std::make_tuple(0, 255, 0), std::make_tuple(0, 0, 255) }; // Color

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
		// Measure deltaTime since last frame
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
			
			ViewPoint vp = WorldToView(p[i].position);
			r.x = (int)vp.x;
			r.y = (int)vp.y;

			// Set color of particle
			SDL_SetRenderDrawColor( renderer, std::get<0>(c[i]), std::get<1>(c[i]), std::get<2>(c[i]), 255 );

			// Draw particle on rederer
			SDL_RenderFillRect( renderer, &r );

			// Reset color to black
			SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		}

    	SDL_RenderPresent(renderer);
	}
	// EVENT LOOP //
	////////////////


    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}