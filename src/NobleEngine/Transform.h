#include <iostream>
#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "Component.h"

namespace NobleEngine
{
	struct Transform : public Component<Transform>
	{
		//static std::vector<std::shared_ptr<Transform>> transformComponents;

		Transform()
		{
			std::cout << "Created Transform" << std::endl;
		}

		/**
		*Contains the position of the transform. Defaults to the origin.
		*/
		glm::vec3 position = glm::vec3(0, 0, 0);
		/**
		*Contains the rotation of the transform. Defaults with no rotation.
		*/
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		/**
		*Contains the scale of the transform. Defaults to a scale of 1 on each
		*/
		glm::vec3 scale = glm::vec3(1,1,1);
		/**
		*Contains the model matrix for use in rendering.
		*/
		glm::mat4 model;
	};
}