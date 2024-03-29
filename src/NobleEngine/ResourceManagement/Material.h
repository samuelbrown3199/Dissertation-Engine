#pragma once
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <GL/glew.h>

#include "Texture.h"

namespace NobleEngine
{
	/**
	*Stores the visual properties of a mesh renderer.
	*/
	struct Material : public Resource
	{
		//after changing and adding variables make sure to update the load material function in the resource manager.
		/**
		*Stores the diffuse texture of the material.
		*/
		std::shared_ptr<Texture> diffuseTexture;
		/**
		*Stores the specular texture of the material.
		*/
		std::shared_ptr<Texture> specularTexture;
		/**
		*Stores the shininess of the texture.
		*/
		float shininess = 1;
	};
}

#endif