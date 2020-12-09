#include "Resource.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

#include <GL/glew.h>

namespace NobleEngine
{
	struct Shader : public Resource
	{
		const GLchar* shaderSource;

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

			std::string shaderCode = shaderStream.str();
			shaderSource = shaderCode.c_str();

			std::cout << shaderSource << std::endl;
		}
	};
}