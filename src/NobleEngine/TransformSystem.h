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
			std::cout << "Transform system update." << std::endl;
		}
	};
}