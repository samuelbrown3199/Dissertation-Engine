#pragma once
#ifndef MODEL_H_
#define MODEL_H_

#include "Resource.h"

#include "bugl.h"

namespace NobleEngine
{
	/**
	*Stores a model file that is loaded with the .obj format.
	*/
	struct Model : public Resource
	{
		GLuint vaoID;
		size_t drawCount;

		void OnLoad()
		{
			vaoID = buLoadModel(resourcePath, &drawCount);
		}
	};
}

#endif