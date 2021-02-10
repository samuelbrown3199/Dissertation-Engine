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
	struct UIRect
	{
		glm::vec2 screenPosition;
		glm::vec2 rectRotation;
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
			rectRotation = glm::vec2(0, 0);
			rectScale = _rectScale;
		}

		UIRect(glm::vec2 _screenPos, glm::vec2 _rectRotation, glm::vec2 _rectScale)
		{
			texture = ResourceManager::LoadResource<Texture>("Resources\\Textures\\test.png");

			screenPosition = _screenPos;
			rectRotation = _rectRotation;
			rectScale = _rectScale;
		}

		glm::mat4 GetUIMatrix()
		{
			glm::mat4 uiMat(1.0f);

			uiMat = glm::translate(uiMat, glm::vec3(screenPosition, -0.1f));
			uiMat = glm::rotate(uiMat, glm::radians(rectRotation.x), glm::vec3(0, 0, 1));
			uiMat = glm::rotate(uiMat, glm::radians(rectRotation.y), glm::vec3(0, 1, 0));
			uiMat = glm::scale(uiMat, glm::vec3(rectScale, 1.0f));

			return uiMat;
		}

		void TempRender()
		{
			Application::standardShaderUI->UseProgram();
			Application::standardShaderUI->BindMat4("u_UIPos", GetUIMatrix());
			Application::standardShaderUI->BindMat4("u_Ortho", Screen::GenerateOrthographicMatrix());

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