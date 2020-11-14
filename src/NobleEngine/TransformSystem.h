#include <iostream>

#include "System.h"
#include "Transform.h"

namespace NobleEngine
{
	struct TransformSystem : public System
	{
		void Initialize()
		{
			
		}
		void Update()
		{
			std::cout << "Size of the transform list is " << transformComponents.size() << std::endl;

			for (size_t tr = 0; tr < transformComponents.size(); tr++)
			{
				GenerateModelMatrix(transformComponents.at(tr));
			}
		}

		void GenerateModelMatrix(std::shared_ptr<Transform> tr)
		{
			std::cout << "Generated a model matrix" << std::endl;
		}
	};
}