#include <iostream>

#include<glm/glm.hpp>
#include <glm/ext.hpp>

#include "System.h"
#include "Transform.h"

namespace NobleEngine
{
	struct TransformSystem : public System
	{
		void Initialize();
		void Update();
		void GenerateModelMatrix(std::shared_ptr<Transform> tr);
	};
}