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
		unsigned int priority;

		static std::shared_ptr<ShaderLocation> CreateLocation(GLuint _shaderProgram, std::string _location)
		{
			std::shared_ptr<ShaderLocation> rtn = std::make_shared<ShaderLocation>();
			rtn->locationName = _location;
			rtn->locationID = glGetUniformLocation(_shaderProgram, _location.c_str());
			rtn->priority = 0;
			if (rtn->locationID == -1)
			{
				//std::cout << "Couldn't find location " << location << " in shader program " << shaderProgram << std::endl;
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

		std::weak_ptr<ShaderProgram> self;
		std::vector<std::shared_ptr<ShaderLocation>> shaderLocations;

		static bool SortByPriority(std::shared_ptr<ShaderLocation>& _loc1, std::shared_ptr<ShaderLocation>& _loc2);

	public:
		ShaderProgram(std::weak_ptr<Application> _app);
		/**
		*Gets a location from the list, or if it does not contain it creates and adds it to list.
		*/
		GLint GetLocation(std::string _location);
		/**
		*Binds a shader resource to the shader program.
		*/
		void BindShader(std::shared_ptr<Shader> _shader, GLenum _shaderType);
		/**
		*Binds a shader source code string to the shader program.
		*/
		void BindShader(const GLchar* _shaderSourceString, GLenum _shaderType);
		/**
		*This function binds an integer to a uniform int in the shader.
		*/
		void BindInt(std::string _location, int _value);
		/**
		*This function binds an float to a uniform int in the shader.
		*/
		void BindFloat(std::string _location, float _value);
		/**
		*This function binds an matrix4 to a uniform matrix4 in the shader.
		*/
		void BindMat4(std::string _location, glm::mat4 _matrix);
		/**
		*This function binds an vec3 to a uniform vec3 in the shader.
		*/
		void BindVector3(std::string _location, glm::vec3 _vector);
		/**
		*Binds the model matrix.
		*/
		void BindModelMat(glm::mat4 _matrix);
		/**
		*Binds the projection matrix.
		*/
		void BindProjectionMat(glm::mat4 _matrix);
		/**
		*Binds the view matrix.
		*/
		void BindViewMat(glm::mat4 _matrix);
		/**
		*Links the program for use in the engine. Also responsible for setting up the uniform variables in the shader code. If this function isn't called then the shader program cannot be used.
		*/
		void LinkShaderProgram(std::shared_ptr<ShaderProgram> _selfPtr);
		/**
		*Sets the currently used shader program to this.
		*/
		void UseProgram();
	};
}
#endif