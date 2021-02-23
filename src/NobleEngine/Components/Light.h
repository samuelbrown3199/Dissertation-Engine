#pragma once
#ifndef LIGHT_H_
#define LIGHT_H_

#include "../EngineCore/Component.h"
#include "../EngineCore/Entity.h"
#include "Transform.h"

#include "glm/glm.hpp"

namespace NobleEngine
{
	struct Light : public Component<Light>
	{
		enum LightType
		{
			Point,
			Directional
		};
		/**
		*Stores the type of light this is.
		*/
		LightType type;
		/**
		*Stores the lights transform component.
		*/
		std::shared_ptr<Transform> lightTransform;
		/**
		*Stores the lights diffuse colour.
		*/
		glm::vec3 diffuseColour;
		/**
		*Stores the lights specular colour.
		*/
		glm::vec3 specularColour;
		/**
		*Stores the lights constant value.
		*/
		float constant;
		/**
		*Stores the lights linear value.
		*/
		float linear;
		/**
		*Stores the lights quadratic value.
		*/
		float quadratic;
		/**
		*Stores the lights intensity value.
		*/
		float intensity;

		/**
		*Initializes a light with default settings.
		*/
		void OnInitialize()
		{
			type = LightType::Directional;

			lightTransform = GetEntity()->GetComponent<Transform>();
			if (!lightTransform)
			{
				std::cout << "No transform attached to light! Adding transform at position (0,0,0)." << std::endl;
				lightTransform = GetEntity()->AddComponent<Transform>(glm::vec3(0,0,0));
			}

			diffuseColour = glm::vec3(1, 1, 1);
			specularColour = glm::vec3(1, 1, 1);

			constant = 1.0f;
			linear = 0.09f;
			quadratic = 0.032f;
			intensity = 1;
		}

		void OnInitialize(LightType _type)
		{
			type = _type;

			lightTransform = GetEntity()->GetComponent<Transform>();
			if (!lightTransform)
			{
				std::cout << "No transform attached to light! Adding transform at position (0,0,0)." << std::endl;
				lightTransform = GetEntity()->AddComponent<Transform>(glm::vec3(0, 0, 0));
			}

			diffuseColour = glm::vec3(1, 1, 1);
			specularColour = glm::vec3(1, 1, 1);

			constant = 1.0f;
			linear = 0.09f;
			quadratic = 0.032f;
			intensity = 1;
		}
	};
}

#endif