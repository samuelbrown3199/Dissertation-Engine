#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<GL/glew.h>

#include "../EngineCore/Resource.h"

namespace NobleEngine
{
    /**
    *Stores a texture for use in the engine.
    */
    struct Texture : public Resource
    {
        GLuint textureID;

        void OnLoad();
    };
}

#endif // !TEXTURE_H_