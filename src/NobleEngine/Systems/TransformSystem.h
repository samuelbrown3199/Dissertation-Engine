#include <iostream>

#include<glm/glm.hpp>
#include <glm/ext.hpp>

#include "../EngineCore/System.h"
#include "../Components/Transform.h"

namespace NobleEngine
{
	/**
	*Handles the generation of model matrices for transform components. Automatically bound to the engine on startup.
	*/
	struct TransformSystem : public System<Transform>
	{
		/**
		*Creates the model matrix of the passed in transform.
		*/
		void OnUpdate(std::shared_ptr<Transform> comp);
		void FixRotation(float value);
	};
}