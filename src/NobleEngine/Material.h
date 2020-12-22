#include <GL/glew.h>

#include "Texture.h"

namespace NobleEngine
{
	struct Material
	{
		//after changing and adding variables make sure to update the load material function in the resource manager.

		std::shared_ptr<Texture> diffuseTexture, specularTexture;
	};
}