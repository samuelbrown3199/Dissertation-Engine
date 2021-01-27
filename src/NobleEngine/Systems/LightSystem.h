#pragma once
#ifndef LIGHTSYSTEM_H_
#define LIGHTSYSTEM_H_

#include "../EngineCore/System.h"
#include "../Components/Light.h"

namespace NobleEngine
{
	struct LightSystem : public System<Light>
	{
		void PreRender();
		void OnRender(std::shared_ptr<Light> comp);
	};
}

#endif