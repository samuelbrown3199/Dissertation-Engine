#pragma once
#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "../EngineCore/Component.h"

#include "../ResourceManagement/SpriteSheet.h"
#include "../ResourceManagement/Model.h"
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
			rendererVAO = PrimitiveShapes::quadVAO;
		}

		void OnInitialize(std::string _sheetLoc)
		{
			transform = GetEntity()->GetComponent<Transform>();
			rendererVAO = PrimitiveShapes::quadVAO;

			sheet = ResourceManager::LoadResource<SpriteSheet>(_sheetLoc);
		}

		void OnInitialize(std::string _sheetLoc, std::string _spriteName, int _x, int _y, int _w, int _h)
		{
			transform = GetEntity()->GetComponent<Transform>();
			rendererVAO = PrimitiveShapes::quadVAO;

			sheet = ResourceManager::LoadResource<SpriteSheet>(_sheetLoc);
			sprite = sheet->GetSpriteLocation(_spriteName, _x, _y, _w, _h);
		}
	};
}

#endif // !SPRITERENDERER_H_
