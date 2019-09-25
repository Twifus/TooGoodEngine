#include "Sprite.hpp"

namespace TooGoodEngine
{

	// This function converts a position in the game world to a point of the viewport
	Vector3 WorldToView(Vector3 pos)
	{
		return Vector3(
			(pos.x / PIXEL_UNIT) + (double)(2 * AXIS_OFFSET + AXIS_WIDTH / 2) - BOX_SIZE / 2,
			VIEW_HEIGHT - (pos.y / PIXEL_UNIT) - (double)(2 * AXIS_OFFSET + AXIS_WIDTH / 2) - BOX_SIZE / 2,
			0
		);
	}

	Sprite::Sprite(Particle* p)
	{
		parent = p;
		Vector3 screenPos = WorldToView(p->GetPosition());
		rect.x = screenPos.x;
		rect.y = screenPos.y;
		rect.w = rect.h = p->GetMass() * 5;
	}

	Sprite::Draw(SDL_Renderer* renderer)
	{
		Vector3 screenPos = WorldToView(parent->position);
		rect.x = screenPos.x;
		rect.y = screenPos.y;

		//TODO : couleur et ligne en dessous

		// Set color of particle
		SDL_SetRenderDrawColor(renderer, std::get<0>(color), std::get<1>(color), std::get<2>(color), 255);

		// Draw particle on rederer
		SDL_RenderFillRect(renderer, &rect);

		// Reset color to black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}




	// This funtion draw white axes on the given renderer. It helps locating particles in the world space.
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
}
