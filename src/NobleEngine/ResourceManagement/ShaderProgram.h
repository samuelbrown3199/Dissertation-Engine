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

	/**
	*Made up of several shader resources, these are used in rendering graphics within the engine.
	*/
	struct ShaderProgram
	{
		std::weak_ptr<Application> application;
		GLuint programID;

	public:
		ShaderProgram(std::weak_ptr<Application> app);
		/**
		*Binds a shader resource to the shader program.
		*/
		void BindShader(std::shared_ptr<Shader> shader, GLenum shaderType);
		/**
		*This function binds an integer to a uniform int in the shader.
		*/
		void BindInt(std::string location, int value);
		/**
		*This function binds an matrix4 to a uniform matrix4 in the shader.
		*/
		void BindMat4(std::string location, glm::mat4 matrix);
		/**
		*Links the program for use in the engine.
		*/
		void LinkShaderProgram();
		/**
		*Sets the currently used shader program to this.
		*/
		void UseProgram();
	};
}
#endif