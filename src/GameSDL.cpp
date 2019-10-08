#include "GameSDL.hpp"
#include <algorithm>

namespace TooGoodEngine
{
    // This function draw white axes on the given renderer. It helps locating particles in the world space.
	void DrawAxes(SDL_Renderer* renderer)
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
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderFillRect(renderer, &xaxis);
		SDL_RenderFillRect(renderer, &yaxis);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

    // Constructor
    GameSDL::GameSDL()
    {
        // Create a SDL window
        window = SDL_CreateWindow("Simulation de tir", 
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  VIEW_WIDTH, VIEW_HEIGHT,
                                  SDL_WINDOW_SHOWN);

        // Create a renderer
        renderer = SDL_CreateRenderer(window, -1, 0);

        // Select the color for drawing : black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }

    // Destructor
    GameSDL::~GameSDL()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Add a particle sprite to the environment
    void GameSDL::CreateSprite(Particle* p,  const char* spritePath)
    {
		Sprite s = Sprite(p, spritePath, renderer);
		sprites.push_back(s);
    }

    void GameSDL::DeleteSprite(Particle* p)
    {
        auto i = std::find_if(sprites.begin(), sprites.end(), [p](Sprite& s){return s.SameParent(p);});
        if (i != sprites.end())
            sprites.erase(i);
    }

    // Event management
    int GameSDL::HandleEvents()
    {
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return -1;
			}
		}
        return 0;
    }

    // Draw all particles and refresh the screen
    void GameSDL::render()
    {
		SDL_RenderClear(renderer);
        for(Sprite& s : sprites)
        {
            s.Draw(renderer);
        }
        SDL_RenderPresent(renderer);
    }
}