#pragma once
#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <string>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Shader.h"

namespace NobleEngine
{
	class Application;

	struct ShaderProgram
	{
		std::weak_ptr<Application> application;
		GLuint programID;

	public:
		ShaderProgram(std::weak_ptr<Application> app);
		void BindShader(std::string shaderDirectory, GLenum shaderType);
		void BindShader(std::shared_ptr<Shader> shader, GLenum shaderType);
		void BindMat4(std::string location, glm::mat4 matrix);
		void LinkShaderProgram();

		void UseProgram();
	};
}
#endif