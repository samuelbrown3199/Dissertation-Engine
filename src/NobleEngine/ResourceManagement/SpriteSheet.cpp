#include "SpriteSheet.h"
#include "../EngineCore/ResourceManager.h"

namespace NobleEngine
{
	void SpriteSheet::OnLoad()
	{
		sheet = ResourceManager::LoadResource<Texture>(resourcePath);
	}

	std::shared_ptr<Sprite> SpriteSheet::CreateSpriteLocation(std::string spriteName, int x, int y, int width, int height)
	{
		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	}
}