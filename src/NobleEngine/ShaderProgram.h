#include <string>
#include <iostream>

#include <GL/glew.h>

#include "Shader.h"

namespace NobleEngine
{
	struct ShaderProgram
	{
		GLuint programID;

		ShaderProgram()
		{
			programID = glCreateProgram();
		}

		void BindShader(std::string shaderDirectory, GLenum shaderType)
		{
			std::shared_ptr<Shader> shader =
		}
	};
}