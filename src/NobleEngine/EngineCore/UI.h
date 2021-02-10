#pragma once
#ifndef UI_H_
#define UI_H_

#include <GL/glew.h>
#include<glm/glm.hpp>

#include "Application.h"
#include "ResourceManager.h"
#include "Screen.h"

#include "../ResourceManagement/ShaderProgram.h"
#include "../ResourceManagement/Model.h"
#include "../ResourceManagement/Texture.h"

namespace NobleEngine
{
	struct UIQuad
	{
		static GLuint quadVAO;
		static std::shared_ptr<ShaderProgram> uiShader;

		static void CreateUIQuad()
		{
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

			uiMat = glm::translate(uiMat, glm::vec3(screenPosition, -0.1f));
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
			glBindVertexArray(PrimitiveShapes::quadVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
			glUseProgram(0);
		}
	};
}

#endif