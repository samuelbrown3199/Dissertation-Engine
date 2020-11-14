#include "glm/glm.hpp"

#include "Component.h"

namespace NobleEngine
{
	struct Transform : public Component
	{
		/**
		*Contains the position of the transform.
		*/
		glm::vec3 position;
		/**
		*Contains the rotation of the transform.
		*/
		glm::vec3 rotation;
		/**
		*Contains the scale of the transform.
		*/
		glm::vec3 scale;
	};
}