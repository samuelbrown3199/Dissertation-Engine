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
		float distanceToCamera;
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
			lightTransform = GetEntity()->GetComponent<Transform>();
			if (!lightTransform)
			{
				std::cout << "No transform attached to light! Adding transform at position (0,0,0)." << std::endl;
				lightTransform = GetEntity()->AddComponent<Transform>(glm::vec3(0, 0, 0));
			}

			diffuseColour = glm::vec3(1, 1, 1);
			specularColour = glm::vec3(1, 1, 1);

			constant = 1.0f;
			linear = 0.045f;
			quadratic = 0.0075f;
			intensity = 1;
		}

		void OnInitialize(glm::vec3 _diffuseColour, glm::vec3 _specularColour, float _linear, float _quadratic, float _intensity)
		{
			lightTransform = GetEntity()->GetComponent<Transform>();
			if (!lightTransform)
			{
				std::cout << "No transform attached to light! Adding transform at position (0,0,0)." << std::endl;
				lightTransform = GetEntity()->AddComponent<Transform>(glm::vec3(0, 0, 0));
			}

			diffuseColour = _diffuseColour;
			specularColour = _specularColour;

			constant = 1.0f;
			linear = _linear;
			quadratic = _quadratic;
			intensity = _intensity;
		}
	};
}

#endif