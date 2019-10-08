#include "Sprite.hpp"

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

	// This function converts a position in the game world to a point of the viewport
	Vector3 WorldToView(Vector3 pos)
	{
		return Vector3(
			(pos.x / PIXEL_UNIT) + static_cast<double>(2 * AXIS_OFFSET + AXIS_WIDTH / 2) - BOX_SIZE / 2,
			VIEW_HEIGHT - (pos.y / PIXEL_UNIT) - static_cast<double>(2 * AXIS_OFFSET + AXIS_WIDTH / 2) - BOX_SIZE / 2,
			0
		);
	}

	Sprite::Sprite(Particle* p, const char* spritePath, SDL_Renderer* gameRenderer)
	{
		parent = p;

		Vector3 screenPos = WorldToView(p->position);
		rectDst.x = static_cast<int>(screenPos.x - p->GetRadius());
		rectDst.y = static_cast<int>(screenPos.y - p->GetRadius());
		rectDst.w = rectDst.h = 2 * p->GetRadius();

		texture = LoadImage(spritePath, gameRenderer);

		rectSrc.x = rectSrc.y = 0;
		rectSrc.h = rectSrc.w = 64;
	}

	int Sprite::SameParent(Particle* p)
	{
		return (p == parent);
	}

	void Sprite::Draw(SDL_Renderer* renderer)
	{
		Vector3 screenPos = WorldToView(parent->position);
		rectDst.x = static_cast<int>(screenPos.x - parent->GetRadius());
		rectDst.y = static_cast<int>(screenPos.y - parent->GetRadius());
		SDL_RenderCopy(renderer, texture.get(), nullptr, &rectDst);
	}
}
