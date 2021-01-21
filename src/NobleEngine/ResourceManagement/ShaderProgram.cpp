#include "ShaderProgram.h"

#include "../EngineCore/Application.h"

namespace NobleEngine
{
	ShaderProgram::ShaderProgram(std::weak_ptr<Application> app)
	{
		application = app;
		programID = glCreateProgram();
	}

	GLint ShaderProgram::GetLocation(std::string location)
	{
		for (size_t i = 0; i < shaderLocations.size(); i++)
		{
			if (shaderLocations.at(i)->locationName == location)
			{
				return shaderLocations.at(i)->locationID;
			}
		}

		std::shared_ptr<ShaderLocation> rtn = ShaderLocation::CreateLocation(programID, location);
		shaderLocations.push_back(rtn);
		return rtn->locationID;
	}

	void ShaderProgram::BindShader(std::shared_ptr<Shader> shader, GLenum shaderType)
	{
		const GLchar* shaderSource = shader->shaderCode->c_str();

		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);
		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			std::cout << "Failed to compile shader with path " << shader->resourcePath << "!" << std::endl;

			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

			for (int i = 0; i < errorLog.size(); i++)
			{
				std::cout << errorLog[i];
			}

			glDeleteShader(shaderID);
			throw std::exception();
		}

		glAttachShader(programID, shaderID);
	}

	void ShaderProgram::BindInt(std::string location, int value)
	{
		GLint intLocation = GetLocation(location);
		glUniform1i(intLocation, value);
	}

	void ShaderProgram::BindMat4(std::string location, glm::mat4 matrix)
	{
		GLint matrixLocation = GetLocation(location);
		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderProgram::BindModelMat(glm::mat4 matrix)
	{
		glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void ShaderProgram::BindProjectionMat(glm::mat4 matrix)
	{
		glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void ShaderProgram::BindViewMat(glm::mat4 matrix)
	{
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderProgram::LinkShaderProgram()
	{
		GLint success = 0;
		glLinkProgram(programID);
		glGetProgramiv(programID, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

			for (int i = 0; i < errorLog.size(); i++)
			{
				std::cout << errorLog[i];
			}

			glDeleteProgram(programID);
			throw std::exception();
		}

		glUseProgram(programID);

		modelMatrixLoc = glGetUniformLocation(programID, "u_Model");
		projectionMatrixLoc = glGetUniformLocation(programID, "u_Projection");
		viewMatrixLoc = glGetUniformLocation(programID, "u_View");

		glUseProgram(0);
	}

	void ShaderProgram::UseProgram()
	{
		glUseProgram(programID);
	}
}