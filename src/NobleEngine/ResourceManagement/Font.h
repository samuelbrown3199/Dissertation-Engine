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
	struct Character
	{
		unsigned int textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};

	struct Font : public Resource
	{
		int fontPixelSize = 48;
		std::map<char, Character> characters;

		void OnLoad();
	};
}

#endif