#pragma once

#include "CommonSDL.hpp"
#include "Particle.hpp"

#include <SDL.h>
#include <SDL_image.h>

namespace TooGoodEngine
{
	class Sprite
	{
	private:
		Particle* parent;
		std::shared_ptr<SDL_Texture> texture;
		SDL_Rect rectSrc;
		SDL_Rect rectDst;
	public:
		Sprite(Particle* p,  const char* spritePath, SDL_Renderer* gameRenderer);
		int SameParent(Particle* p);
		void Draw(SDL_Renderer* renderer);
	};

	void DrawAxes(SDL_Renderer* renderer);
}
