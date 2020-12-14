#include "ShaderProgram.h"

#include "Application.h"

namespace NobleEngine
{
	ShaderProgram::ShaderProgram(std::weak_ptr<Application> app)
	{
		application = app;
		programID = glCreateProgram();
	}

	void ShaderProgram::BindShader(std::string shaderDirectory, GLenum shaderType)
	{
		/*std::shared_ptr<Shader> shader = application.lock()->GetResourceManager()->LoadResource(shaderDirectory);
		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shader->shaderSource, NULL);
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
			return;
		}

		glAttachShader(programID, shaderID);*/
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
	}
}