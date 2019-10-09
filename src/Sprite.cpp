#include "Sprite.hpp"
#include <iostream>

namespace TooGoodEngine
{
	// Used to load a png image into the texture
	std::shared_ptr<SDL_Texture> LoadImage(const char* path, SDL_Renderer* gameRenderer)
	{
		SDL_Surface* tmpSurface = IMG_Load(path);
    	SDL_Texture* tex = SDL_CreateTextureFromSurface(gameRenderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		return std::shared_ptr<SDL_Texture>(tex, [](SDL_Texture* tex) { SDL_DestroyTexture(tex); });
	}

	// Position on the screen
	struct PixelPos{int x,y;};
	// This function converts a position in the game world to a point of the viewport
	PixelPos WorldToView(Vector3 pos)
	{
		PixelPos screenPos;
		screenPos.x = static_cast<int>(pos.x * PIXEL_UNIT + VIEW_WIDTH / 2);
		screenPos.y = static_cast<int>(-pos.y * PIXEL_UNIT + VIEW_HEIGHT / 2);
		return screenPos;
	}

	void Sprite::UpdateRectDest()
	{
		// Radius (pixel)
		int dstToCenterPos = static_cast<int>(parent->GetRadius() * PIXEL_UNIT);
		// Position (pixel)
		PixelPos screenPos = WorldToView(parent->position);
		// Set destination rectangle for the texture
		rectDst.x = screenPos.x - dstToCenterPos;
		rectDst.y = screenPos.y - dstToCenterPos;
		rectDst.w = rectDst.h = 2 * dstToCenterPos;
	}

	Sprite::Sprite(Particle* p, const char* spritePath, SDL_Renderer* gameRenderer)
	{
		parent = p;
		UpdateRectDest();
		texture = LoadImage(spritePath, gameRenderer);
	}

	int Sprite::SameParent(Particle* p)
	{
		return (p == parent);
	}

	void Sprite::Draw(SDL_Renderer* renderer)
	{
		UpdateRectDest();
		SDL_RenderCopy(renderer, texture.get(), NULL, &rectDst);
	}
}
