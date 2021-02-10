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
#include "../ResourceManagement/Font.h"

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

			uiMat = glm::translate(uiMat, glm::vec3(screenPosition, 0.0f));
			uiMat = glm::scale(uiMat, glm::vec3(rectScale, 1.0f));

			return uiMat;
		}
	};

	struct UIElement
	{
		std::shared_ptr<UIRect> elementRect;
		std::shared_ptr<Texture> texture;

		virtual void OnRender() {};

		void TempRender()
		{
			Application::standardShaderUI->UseProgram();
			Application::standardShaderUI->BindMat4("u_UIPos", elementRect->GetUIMatrix());
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

	struct UILabel : public UIElement
	{
		std::shared_ptr<Font> labelFont;
		std::string text;

		void OnRender(float x, float y, float scale, glm::vec3 color)
		{
			labelFont = ResourceManager::LoadResource<Font>("Resources\\Fonts\\test.ttf");

			// activate corresponding render state	
			Application::standardShaderText->UseProgram();
			Application::standardShaderText->BindVector3("textColor", color);
			Application::standardShaderText->BindMat4("projection", Screen::GenerateOrthographicMatrix());
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(PrimitiveShapes::textQuadVAO);

			// iterate through all characters
			std::string::const_iterator c;
			for (c = text.begin(); c != text.end(); c++)
			{
				Character ch = labelFont->characters[*c];

				float xpos = x + ch.bearing.x * scale;
				float ypos = y - (ch.size.y - ch.bearing.y) * scale;

				float w = ch.size.x * scale;
				float h = ch.size.y * scale;
				// update VBO for each character
				GLfloat vertices[] = {
					xpos,     ypos + h,
					xpos,     ypos,
					xpos + w, ypos,
					xpos,     ypos + h,
					xpos + w, ypos,
					xpos + w, ypos + h
				};
				GLfloat uvs[] =
				{
					0.0f, 0.0f,
					0.0f, 1.0f,
					1.0f, 1.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 0.0f
				};
				// render glyph texture over quad
				glBindTexture(GL_TEXTURE_2D, ch.textureID);
				// update content of VBO memory
				glBindBuffer(GL_ARRAY_BUFFER, PrimitiveShapes::textQuadPositionVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, PrimitiveShapes::textQuadUVsVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_DYNAMIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// render quad
				glDrawArrays(GL_TRIANGLES, 0, 6);
				// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				x += (ch.advance >> 6)* scale; // bitshift by 6 to get value in pixels (2^6 = 64)
			}
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	};
}

#endif