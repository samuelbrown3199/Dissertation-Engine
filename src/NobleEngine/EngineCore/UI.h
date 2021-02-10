#pragma once
#ifndef UI_H_
#define UI_H_

#include <GL/glew.h>
#include<glm/glm.hpp>

#include "Application.h"
#include "ResourceManager.h"
#include "Screen.h"

#include "../ResourceManagement/ShaderProgram.h"
#include "../ResourceManagement/Texture.h"

namespace NobleEngine
{
	struct UIQuad
	{
		static GLuint quadVAO;
		static std::shared_ptr<ShaderProgram> uiShader;

		static void CreateUIQuad()
		{
			const GLfloat positions[] =
			{
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f
			};

			const GLfloat uvs[] =
			{
				0.0, 0.0,
				0.0, 1.0,
				1.0, 1.0,
				1.0, 1.0,
				1.0, 0.0,
				0.0, 0.0
			};

			GLuint positionsVBO = 0;
			glGenBuffers(1, &positionsVBO);
			if (!positionsVBO)
			{
				throw std::exception();
			}
			glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint uvVBO = 0;
			glGenBuffers(1, &uvVBO);
			if (!uvVBO)
			{
				throw std::exception();
			}
			glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenVertexArrays(1, &quadVAO);
			if (!quadVAO)
			{
				throw std::exception();
			}
			glBindVertexArray(quadVAO);

			glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);

			std::shared_ptr<Shader> vertexShader = ResourceManager::LoadResource<Shader>("Resources\\Shaders\\uiStandard.vs");
			std::shared_ptr<Shader> fragmentShader = ResourceManager::LoadResource<Shader>("Resources\\Shaders\\uiStandard.fs");
			uiShader = std::make_shared<ShaderProgram>(Application::self);
			uiShader->BindShader(vertexShader, GL_VERTEX_SHADER);
			uiShader->BindShader(fragmentShader, GL_FRAGMENT_SHADER);
			uiShader->LinkShaderProgram(uiShader);
		}
	};

	struct UIRect
	{
		glm::vec2 screenPosition;
		glm::vec2 rectScale;

		std::shared_ptr<Texture> texture;

		UIRect()
		{
			texture = ResourceManager::LoadResource<Texture>("Resources\\Textures\\test.png");
		}

		UIRect(glm::vec2 _screenPos, glm::vec2 _rectScale)
		{
			texture = ResourceManager::LoadResource<Texture>("Resources\\Textures\\test.png");

			screenPosition = _screenPos;
			rectScale = _rectScale;
		}

		glm::mat4 GetUIMatrix()
		{
			glm::mat4 uiMat(1.0f);

			uiMat = glm::translate(uiMat, glm::vec3(screenPosition, 0.0f));
			uiMat = glm::scale(uiMat, glm::vec3(rectScale, 1.0f));

			return uiMat;
		}

		void TempRender()
		{
			UIQuad::uiShader->UseProgram();
			UIQuad::uiShader->BindMat4("u_UIPos", GetUIMatrix());
			UIQuad::uiShader->BindMat4("u_Ortho", Screen::GenerateOrthographicMatrix());

			if (texture)
			{
				glActiveTexture(0);
				glBindTexture(GL_TEXTURE_2D, texture->textureID);
			}
			glBindVertexArray(UIQuad::quadVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
			glUseProgram(0);
		}
	};
}

#endif