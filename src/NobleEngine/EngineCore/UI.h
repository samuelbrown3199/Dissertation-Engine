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
		glm::vec2 rectScale;

		UIRect()
		{
			screenPosition = glm::vec2(0, 0);
			rectScale = glm::vec2(0, 0);
		}

		UIRect(glm::vec2 _screenPos, glm::vec2 _rectScale)
		{
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
	};

	struct UIElement
	{
		UIRect elementRect;
		std::shared_ptr<Texture> texture;

		virtual void OnRender();

		void TempRender()
		{
			Application::standardShaderUI->UseProgram();
			Application::standardShaderUI->BindMat4("u_UIPos", elementRect.GetUIMatrix());
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