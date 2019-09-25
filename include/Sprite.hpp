#pragma once

#define VIEW_WIDTH 1280
#define VIEW_HEIGHT 720

#define PIXEL_UNIT 0.01

#define BOX_SIZE 16

#define AXIS_WIDTH 4
#define AXIS_OFFSET 5

#include "Particle.hpp"
#include <SDL.h>

namespace TooGoodEngine
{
	class Sprite
	{
	private:
		SDL_Rect rect;
		int color[3];
		Particle* parent;
	public:
		Sprite(Particle* p,  int r = 255, int g = 0, int b = 0);
		void Draw(SDL_Renderer* renderer);
	};

	void DrawAxes(SDL_Renderer* renderer);
}
