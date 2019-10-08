#pragma once

#include <SDL.h>
#include <vector>
#include "CommonSDL.hpp"
#include "Sprite.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
    class GameSDL
    {
    private:
        SDL_Event event;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<Sprite> sprites;

        SDL_Renderer* initRenderer();

    public:
        GameSDL();
        ~GameSDL();

        void CreateSprite(Particle* p,  const char* spritePath);
        void DeleteSprite(Particle* p);

        int HandleEvents();
        void render();
    };
}