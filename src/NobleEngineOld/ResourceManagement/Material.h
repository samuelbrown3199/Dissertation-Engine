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
	struct Material
	{
		//after changing and adding variables make sure to update the load material function in the resource manager.

		std::shared_ptr<Texture> diffuseTexture, specularTexture;
	};
}

#endif