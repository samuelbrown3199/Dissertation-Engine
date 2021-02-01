#include "SpriteSheet.h"
#include "../EngineCore/ResourceManager.h"

namespace NobleEngine
{
	void SpriteSheet::OnLoad()
	{
		sheet = ResourceManager::LoadResource<Texture>(resourcePath);
	}

	std::shared_ptr<Sprite> SpriteSheet::GetSpriteLocation(std::string spriteName, int x, int y, int width, int height)
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites.at(i)->spriteName == spriteName)
			{
				return sprites.at(i);
			}
		}
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(spriteName);
		float xPosition = (1 / sheet->w) * x;
		float yPosition = (1 / sheet->h) * y;
		float wPosition = (1 / sheet->w) * width;
		float hPosition = (1 / sheet->h) * height;

		sprite->xPos = xPosition;
		sprite->yPos = yPosition;
		sprite->width = wPosition;
		sprite->height = hPosition;

		sprites.push_back(sprite);

		return sprite;
	}

	std::shared_ptr<Sprite> SpriteSheet::GetSpriteLocation(std::string spriteName)
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites.at(i)->spriteName == spriteName)
			{
				return sprites.at(i);
			}
		}

		std::cout << "Could not find sprite with name " << spriteName << " on sprite sheet called " << resourcePath << std::endl;
		return nullptr;
	}
}