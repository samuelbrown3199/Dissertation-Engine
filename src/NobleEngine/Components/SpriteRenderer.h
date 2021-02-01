#pragma once
#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "../EngineCore/Component.h"

#include "../ResourceManagement/SpriteSheet.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "../EngineCore/Entity.h"
#include "../EngineCore/ResourceManager.h"
#include "Transform.h"

namespace NobleEngine
{
	/**
	*Renders a sprite onto the screen.
	*/
	struct SpriteRenderer : public Component<SpriteRenderer>
	{
		std::shared_ptr<SpriteSheet> sheet;
		std::shared_ptr<Sprite> sprite, oldSprite;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<ShaderProgram> shader;

		GLuint rendererVAO;

		void OnInitialize()
		{
			transform = GetEntity()->GetComponent<Transform>();
		}

		void OnInitialize(std::string sheetLoc, std::string spriteName, int x, int y, int w, int h)
		{
			transform = GetEntity()->GetComponent<Transform>();

			sheet = ResourceManager::LoadResource<SpriteSheet>(sheetLoc);
			sprite = sheet->GetSpriteLocation(spriteName, x, y, w, h);
		}
	};
}

#endif // !SPRITERENDERER_H_
