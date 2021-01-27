#pragma once
#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Shader.h"

namespace NobleEngine
{
	class Application;

	/**
	*Stores a shader location GLint. It is more optimal to store these rather than to find them every frame.
	*/
	struct ShaderLocation
	{
		std::string locationName;
		GLint locationID;

		static std::shared_ptr<ShaderLocation> CreateLocation(GLuint shaderProgram, std::string location)
		{
			std::shared_ptr<ShaderLocation> rtn = std::make_shared<ShaderLocation>();
			rtn->locationName = location;
			rtn->locationID = glGetUniformLocation(shaderProgram, location.c_str());
			if (rtn->locationID == -1)
			{
				std::cout << "Couldn't find location " << location << " in shader program " << shaderProgram << std::endl;
			}

			return rtn;
		}
	};
	/**
	*Made up of several shader resources, these are used in rendering graphics within the engine.
	*/
	struct ShaderProgram
	{
		std::weak_ptr<Application> application;
		GLuint programID;

		GLint modelMatrixLoc, projectionMatrixLoc, viewMatrixLoc;

		std::vector<std::shared_ptr<ShaderLocation>> shaderLocations;

	public:
		ShaderProgram(std::weak_ptr<Application> app);
		/**
		*Gets a location from the list, or if it does not contain it creates and adds it to list.
		*/
		GLint GetLocation(std::string location);
		/**
		*Binds a shader resource to the shader program.
		*/
		void BindShader(std::shared_ptr<Shader> shader, GLenum shaderType);
		/**
		*This function binds an integer to a uniform int in the shader.
		*/
		void BindInt(std::string location, int value);
		/**
		*This function binds an float to a uniform int in the shader.
		*/
		void BindFloat(std::string location, float value);
		/**
		*This function binds an matrix4 to a uniform matrix4 in the shader.
		*/
		void BindMat4(std::string location, glm::mat4 matrix);
		/**
		*This function binds an vec3 to a uniform vec3 in the shader.
		*/
		void BindVector3(std::string location, glm::vec3 vector);
		/**
		*Binds the model matrix.
		*/
		void BindModelMat(glm::mat4 matrix);
		/**
		*Binds the projection matrix.
		*/
		void BindProjectionMat(glm::mat4 matrix);
		/**
		*Binds the view matrix.
		*/
		void BindViewMat(glm::mat4 matrix);
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