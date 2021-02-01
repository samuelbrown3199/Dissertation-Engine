#pragma once
#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "../EngineCore/Component.h"

#include "../ResourceManagement/SpriteSheet.h"
#include "../EngineCore/Entity.h"
#include "Transform.h"

namespace NobleEngine
{
	struct SpriteRenderer : public Component<SpriteRenderer>
	{
		std::shared_ptr<Sprite> sprite;
		std::shared_ptr<Transform> transform;

		void OnInitialize()
		{
			transform = GetEntity()->GetComponent<Transform>();
		}
	};
}

#endif // !SPRITERENDERER_H_
