#include <iostream>

#include<glm/glm.hpp>
#include <glm/ext.hpp>

#include "System.h"
#include "Transform.h"

namespace NobleEngine
{
	/**
	*Handles the generation of model matrices for transform components. Automatically bound to the engine on startup.
	*/
	struct TransformSystem : public System<Transform>
	{
		void OnUpdate(std::shared_ptr<Transform> comp);
		/**
		*Creates the model matrix of the passed in transform.
		*/
		void GenerateModelMatrix(std::shared_ptr<Transform> tr);
	};
}