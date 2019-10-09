#include "GameSDL.hpp"
#include <algorithm>

namespace TooGoodEngine
{
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