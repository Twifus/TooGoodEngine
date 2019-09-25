#include <iostream>
#include <SDL.h>
#include <vector>
#include <tuple>
#include "Vector3.hpp"
#include "Particle.hpp"
#include "Frame.hpp"

#define VIEW_WIDTH 1280
#define VIEW_HEIGHT 720

#define PIXEL_UNIT 0.01

#define BOX_SIZE 16

#define AXIS_WIDTH 4
#define AXIS_OFFSET 5

using namespace TooGoodEngine;

// Class representing a point of the viewport
class ViewPoint
{
public:
	double x, y;
	ViewPoint(double x, double y) : x(x), y(y) {}
};

// This function converts a position in the game world to a point of the viewport
ViewPoint WorldToView(Vector3 pos)
{
	return ViewPoint((pos.x / PIXEL_UNIT) + (double)(2 * AXIS_OFFSET + AXIS_WIDTH / 2) - BOX_SIZE / 2, VIEW_HEIGHT - (pos.y / PIXEL_UNIT) - (double)(2 * AXIS_OFFSET + AXIS_WIDTH / 2) - BOX_SIZE / 2);
}

// This function draw white axes on the given renderer. It helps locating particles in the world space.
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

int main (void)
{
	// Create a SDL window
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Simulation de tir", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	if (!window)
		return EXIT_FAILURE;

    // Create a renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, 0);

	if (!renderer)
		return EXIT_FAILURE;

	// Set background to black
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

	SDL_Rect r;
	r.w = BOX_SIZE;
	r.h = BOX_SIZE;
	SDL_Event event;
	
	// Particle initialization
	Frame f = Frame();
	std::vector<Particle> p = { Particle(), Particle(3, 0.7), Particle(5, 0.5) }; // Particle
	std::vector<Vector3> p0 = { Vector3(0, 7, 0), Vector3(0, 5, 0), Vector3() }; // Initial pos
	std::vector<Vector3> v = { Vector3(), Vector3(10, 0, 0), Vector3(10, 15, 0) }; // Initial velocity
	std::vector<std::tuple<int, int, int>> c = { std::make_tuple(255, 0, 0), std::make_tuple(0, 255, 0), std::make_tuple(0, 0, 255) }; // Color

	for (int i = 0; i < p.size(); ++i)
	{
		p[i].position = p0[i];
		p[i].velocity = v[i];
	}

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
		for (auto &i : p)
		{
			i.Update(f.getDeltaFrame());
		}

		//Loop for particles display
		for (size_t i = 0; i < p.size(); i++)
		{
			
			ViewPoint vp = WorldToView(p[i].position);
			r.x = (int)vp.x;
			r.y = (int)vp.y;

			// Set color of particle
			SDL_SetRenderDrawColor( renderer, std::get<0>(c[i]), std::get<1>(c[i]), std::get<2>(c[i]), 255 );

			// Draw particle on renderer
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