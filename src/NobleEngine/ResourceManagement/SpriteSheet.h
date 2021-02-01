#pragma once
#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include <memory>
#include <vector>
#include <iostream>

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
		float xPos, yPos;
		int width, height;

		Sprite(std::string _name)
		{
			spriteName = _name;
		}
	};

	/**
	*Stores a texture and a list of sprites.
	*/
	struct SpriteSheet : public Resource
	{
		std::shared_ptr<Texture> sheet;
		std::vector<std::shared_ptr<Sprite>> sprites;

		void OnLoad();
		/**
		*Returns a shared pointer to either an already existing sprite on the sheet, or creates a new sprite and returns that.
		*/
		std::shared_ptr<Sprite> GetSpriteLocation(std::string spriteName, int x, int y, int width, int height);
		/**
		*Returns an already existing sprite from the sheet with the same name.
		*/
		std::shared_ptr<Sprite> GetSpriteLocation(std::string spriteName);
	};
}

#endif