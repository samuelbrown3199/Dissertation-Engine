#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <iostream>
#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "Component.h"

namespace NobleEngine
{
	struct PhysicsBody;

	/**
	*Stores a transform component data.
	*/
	struct Transform : public Component<Transform>
	{
		/**
		*Stores a physics body. If a physics body is attached to the same entity then its transform data is used instead.
		*/
		std::shared_ptr<PhysicsBody> pBody;
		bool check = false;
		/**
		*Contains the position of the transform. Defaults to the origin.
		*/
		glm::vec3 position = glm::vec3(0, 0, 0);
		/**
		*Contains the rotation of the transform. Defaults with no rotation.
		*/
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		/**
		*Contains the scale of the transform. Defaults to a scale of 1 on each axis.
		*/
		glm::vec3 scale = glm::vec3(1, 1, 1);
		/**
		*Contains the model matrix for use in rendering.
		*/
		glm::mat4 model;
	};
}

#endif