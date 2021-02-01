#pragma once
#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include <memory>
#include <vector>

#include "../EngineCore/Resource.h"
#include "Texture.h"

namespace NobleEngine
{
	/**
	*Stores UV coordinates to a sprite on a sprite sheet.
	*/
	struct Sprite
	{
		std::string spriteName;
		int xPixelPos, yPixelPos;
		int width, height;
	};

	/**
	*Stores a texture and a list of sprites.
	*/
	struct SpriteSheet : public Resource
	{
		std::shared_ptr<Texture> sheet;
		std::vector<std::shared_ptr<Sprite>> sprites;

		void OnLoad();
		std::shared_ptr<Sprite> CreateSpriteLocation(std::string spriteName, int x, int y, int width, int height);
	};
}

#endif