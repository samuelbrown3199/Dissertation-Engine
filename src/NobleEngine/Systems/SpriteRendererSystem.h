#pragma once
#ifndef SPRITERENDERERSYSTEM_H_
#define SPRITERENDERERSYSTEM_H_

#include "../EngineCore/System.h"
#include "../Components/SpriteRenderer.h"

namespace NobleEngine
{
	struct SpriteRendererSystem : public System<SpriteRenderer>
	{
		void OnRender(std::shared_ptr<SpriteRenderer> _comp);
	};
}

#endif
