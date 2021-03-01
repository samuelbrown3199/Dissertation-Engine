#pragma once
#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Entity.h"
#include "UI.h"

namespace NobleEngine
{
	/**
	*Stores information for a directional light.
	*/
	struct DirectionalLight
	{
		/**
		*Stores the lights diffuse light colour.
		*/
		glm::vec3 diffuseLightColour;
		/**
		*Stores the lights specular light colour.
		*/
		glm::vec3 specularLightColour;
		/**
		*Stores the lights intensity.
		*/
		float intensity;
		/**
		*Stores the direction that the light is facing in.
		*/
		glm::vec3 direction;
		/**
		*Sets up the directional light with default settings.
		*/
		DirectionalLight();
	};
	/**
	*Stores information for environments.
	*/
	struct Environment
	{
		/**
		*Stores the colour of the ambient light using RGB.
		*/
		glm::vec3 ambientLightColour;
		/**
		*Stores the strength of the environments ambient light.
		*/
		float ambientLightStrength;
		/**
		*Stores the environments directional light.
		*/
		std::shared_ptr<DirectionalLight> directionalLight;
		/**
		*Sets up the environment with default settings.
		*/
		Environment();
	};
	/**
	*Stores a scene, with different entities and UIs.
	*/
	struct Scene
	{
		/**
		*Stores the environmental information for the scene.
		*/
		std::shared_ptr<Environment> sceneEnvironment;
		/**
		*Stores the scenes entities.
		*/
		std::vector<std::shared_ptr<Entity>> sceneEntities;
		/**
		*Stores the interfaces of the scene.
		*/
		std::vector<std::shared_ptr<UISystem>> sceneInterfaces;
		/**
		*Sets up a scene with default settings.
		*/
		Scene();
		/**
		*Creates and stores an entity within the scene information.
		*/
		std::shared_ptr<Entity> CreateEntity();

		template<typename T>
		/**
		*Binds the UI system to the scene.
		*/
		std::shared_ptr<T> BindUISystem()
		{
			std::shared_ptr<T> sys = std::make_shared<T>();
			sys->InitializeUI();

			sceneInterfaces.push_back(sys);
			return sys;
		}
	};
}

#endif