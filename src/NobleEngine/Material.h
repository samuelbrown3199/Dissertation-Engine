#include <GL/glew.h>

#include "Texture.h"

namespace NobleEngine
{
	struct Material
	{
		//std::shared_ptr<ShaderProgram> shaderProgram;
		std::shared_ptr<Texture> diffuseTexture, specularTexture;
	};

}