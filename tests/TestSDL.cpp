#include <SDL.h>
#include "Vector3.hpp"
#include "Particle.hpp"

#define VIEW_WIDTH 1280
#define VIEW_HEIGHT 720

#define BOX_SIZE 50

#define AXIS_WIDTH 4
#define AXIS_OFFSET 5

using namespace TooGoodEngine;

class ViewPoint
{
public:
	double x, y;
	ViewPoint(double x, double y) : x(x), y(y) {}
};

ViewPoint WorldToView(Vector3 pos)
{
	return ViewPoint(pos.x - BOX_SIZE / 2, VIEW_HEIGHT - pos.y - BOX_SIZE / 2);
}

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

	// EVENT LOOP
	SDL_Rect r;
	r.w = BOX_SIZE;
	r.h = BOX_SIZE;
	SDL_Event event;
	Vector3 v;
	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}
		SDL_RenderClear(renderer);

		DrawAxes(renderer);

		v.x++;
		v.y++;
		ViewPoint vp = WorldToView(v);

    	r.x = vp.x;
    	r.y = vp.y;

    	// Set color to blue (will change rect color)
    	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    	SDL_RenderFillRect( renderer, &r );

		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    	SDL_RenderPresent(renderer);
	}


    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}