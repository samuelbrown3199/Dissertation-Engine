#pragma once
#ifndef FONT_H_
#define FONT_H_

#include "../EngineCore/Resource.h"

#include<map>

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace NobleEngine
{
	/**
	*Stores a font character texture information.
	*/
	struct Character
	{
		unsigned int textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};
	/**
	*Stores information for a font file. Loaded as a resource.
	*/
	struct Font : public Resource
	{
		/**
		*Determines how big the font should be.
		*/
		int fontPixelSize = 48;
		/**
		*Stores the character information for the font.
		*/
		std::map<char, Character> characters;
		/**
		*Creates a font with a pixel size parameter.
		*/
		Font(int _pixelSize);
		/**
		*Loads the font file.
		*/
		void OnLoad();
	};
}

#endif