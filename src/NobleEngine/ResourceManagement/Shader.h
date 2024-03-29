#pragma once
#ifndef SHADER_H_
#define SHADER_H_

#include "../EngineCore/Resource.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <exception>

#include <GL/glew.h>

namespace NobleEngine
{
	/**
	*Stores a shader source code file.
	*/
	struct Shader : public Resource
	{
		std::shared_ptr<std::string> shaderCode;

		void OnLoad()
		{
			std::ifstream shaderFile;
			shaderFile.open(resourcePath);

			if (!shaderFile.is_open())
			{
				std::cout << "Couldn't find shader file at " << resourcePath << std::endl;
				throw std::exception();
			}
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();

			shaderCode = std::make_shared<std::string>(shaderStream.str());
		}
	};
}

#endif