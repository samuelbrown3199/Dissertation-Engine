#include <string>
#include <iostream>
#include <memory>

#include <GL/glew.h>

#include "Shader.h"

namespace NobleEngine
{
	class Application;

	struct ShaderProgram
	{
		std::weak_ptr<Application> application;
		GLuint programID;

		ShaderProgram(std::weak_ptr<Application> app);
		void BindShader(std::string shaderDirectory, GLenum shaderType);
		void BindShader(std::shared_ptr<Shader> shader, GLenum shaderType);
		void LinkShaderProgram();
	};
}