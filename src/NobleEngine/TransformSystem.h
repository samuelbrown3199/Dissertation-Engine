#include <iostream>

#include<glm/glm.hpp>
#include <glm/ext.hpp>

#include "System.h"
#include "Transform.h"

namespace NobleEngine
{
	struct TransformSystem : public System<Transform>
	{
		void Update();
		/**
		*Creates the model matrix of the passed in transform.
		*/
		void GenerateModelMatrix(std::shared_ptr<Transform> tr);
	};
}