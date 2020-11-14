#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "Component.h"

namespace NobleEngine
{
	struct Transform;
	static std::vector<std::shared_ptr<Transform>> transformComponents;

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