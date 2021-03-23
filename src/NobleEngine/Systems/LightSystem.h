#pragma once
#ifndef LIGHTSYSTEM_H_
#define LIGHTSYSTEM_H_

#include "../EngineCore/System.h"
#include "../Components/Light.h"

namespace NobleEngine
{
	struct LightSystem : public System<Light>
	{
		static bool SortByDistance(std::shared_ptr<Light>& light1, std::shared_ptr<Light>& light2);
		/**
		*Updates the lights distance value to the main camera.
		*/
		void OnUpdate(std::shared_ptr<Light> comp);
		/**
		*Binds the closest 20 lights to the shader.
		*/
		void PreRender();
	};
}

#endif