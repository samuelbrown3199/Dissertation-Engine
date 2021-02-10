#pragma once
#ifndef MODEL_H_
#define MODEL_H_

#include "../EngineCore/Resource.h"

#include "bugl.h"

namespace NobleEngine
{
	/**
	*Stores VAOs for primitive engine shapes.
	*/
	struct PrimitiveShapes
	{
		/**
		*Stores a quad model.
		*/
		static GLuint quadVAO;
		static GLuint textQuadVAO;
		static GLuint textQuadVBO;

		static void SetupQuad();
		static void SetupTextQuad();
		static void SetupPrimitiveShapes();
	};

	/**
	*Stores a model file that is loaded with the .obj format.
	*/
	struct Model : public Resource
	{
		GLuint vaoID;
		size_t drawCount;

		void OnLoad();
	};
}

#endif