#include "UI.h"

namespace NobleEngine
{
	UIRect::UIRect()
	{
		screenPosition = glm::vec2(0, 0);
		rectScale = glm::vec2(0, 0);
	}

	UIRect::UIRect(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _rectScale)
	{
		layer = _layer;
		screenPosition = _screenPos;
		rectScale = _rectScale;
	}

	glm::mat4 UIRect::GetUIMatrix()
	{
		glm::mat4 uiMat(1.0f);

		uiMat = glm::translate(uiMat, glm::vec3(screenPosition, 0.0f));
		uiMat = glm::scale(uiMat, glm::vec3(rectScale, 1.0f));

		return uiMat;
	}

	bool UIRect::IsMouseInRect()
	{
		int xMousePos = InputManager::mouseX;
		int yMousePos = InputManager::mouseY;

		if (xMousePos >= screenPosition.x && xMousePos <= screenPosition.x + rectScale.x)
		{
			if (yMousePos >= screenPosition.y && yMousePos <= screenPosition.y + rectScale.y)
			{
				return true;
			}
		}

		return false;
	}


	//---------------------------------------------------------------------------//

	UIBox::UIBox(unsigned int layer, glm::vec2 screenPos, glm::vec2 scale)
	{
		elementRect = std::make_shared<UIRect>(layer, screenPos, scale);
	}
	UIBox::UIBox(unsigned int layer, glm::vec2 screenPos, glm::vec2 scale, std::string baseTextureLoc)
	{
		elementRect = std::make_shared<UIRect>(layer, screenPos, scale);
		baseTexture = ResourceManager::LoadResource<Texture>(baseTextureLoc);
	}
	UIBox::UIBox(unsigned int layer, glm::vec2 screenPos, glm::vec2 scale, std::string baseTextureLoc, std::string hoverTextureLoc)
	{
		elementRect = std::make_shared<UIRect>(layer, screenPos, scale);
		baseTexture = ResourceManager::LoadResource<Texture>(baseTextureLoc);
		hoverTexture = ResourceManager::LoadResource<Texture>(hoverTextureLoc);
	}
	void UIBox::OnRender()
	{
		Application::standardShaderUI->UseProgram();
		Application::standardShaderUI->BindMat4("u_UIPos", elementRect->GetUIMatrix());
		Application::standardShaderUI->BindMat4("u_Ortho", Screen::GenerateOrthographicMatrix());

		glActiveTexture(0);
		if (baseTexture)
		{
			glBindTexture(GL_TEXTURE_2D, baseTexture->textureID);
		}
		if (hoverTexture)
		{
			if (elementRect->IsMouseInRect())
			{
				glBindTexture(GL_TEXTURE_2D, hoverTexture->textureID);
			}
		}
		glBindVertexArray(PrimitiveShapes::quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	//---------------------------------------------------------------------------//

	UIButton::UIButton(unsigned int layer, glm::vec2 screenPos, glm::vec2 scale)
	{
		pressed = false;
		elementRect = std::make_shared<UIRect>(layer, screenPos, scale);
	}
	UIButton::UIButton(unsigned int layer, glm::vec2 screenPos, glm::vec2 scale, std::string baseTextureLoc, std::string hoverTextureLoc, std::string clickedTextureLoc)
	{
		pressed = false;

		elementRect = std::make_shared<UIRect>(layer, screenPos, scale);
		baseTexture = ResourceManager::LoadResource<Texture>(baseTextureLoc);
		hoverTexture = ResourceManager::LoadResource<Texture>(hoverTextureLoc);
		clickedTexture = ResourceManager::LoadResource<Texture>(clickedTextureLoc);
	}

	void UIButton::OnUpdate()
	{
		if (elementRect->IsMouseInRect())
		{
			if (InputManager::GetMouseButtonDown(0))
			{
				pressed = true;
			}
			else
			{
				pressed = false;
			}
		}
	}

	void UIButton::OnRender()
	{
		Application::standardShaderUI->UseProgram();
		Application::standardShaderUI->BindMat4("u_UIPos", elementRect->GetUIMatrix());
		Application::standardShaderUI->BindMat4("u_Ortho", Screen::GenerateOrthographicMatrix());

		glActiveTexture(0);
		if (baseTexture)
		{
			glBindTexture(GL_TEXTURE_2D, baseTexture->textureID);
		}
		if (hoverTexture)
		{
			if (elementRect->IsMouseInRect())
			{
				if (InputManager::GetMouseButton(0))
				{
					glBindTexture(GL_TEXTURE_2D, clickedTexture->textureID);
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, hoverTexture->textureID);
				}
			}
		}
		glBindVertexArray(PrimitiveShapes::quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	bool UIButton::ClickedOn()
	{
		return pressed;
	}

	//---------------------------------------------------------------------------//

	UILabel::UILabel(unsigned int layer, glm::vec2 screenPos, glm::vec2 scale)
	{
		elementRect = std::make_shared<UIRect>(layer, screenPos, scale);
	}
	void UILabel::OnRender()
	{
		float x = elementRect->screenPosition.x;
		float y = elementRect->screenPosition.y;

		// activate corresponding render state	
		Application::standardShaderText->UseProgram();
		Application::standardShaderText->BindVector3("textColor", color);
		Application::standardShaderText->BindMat4("model", glm::mat4(1.0f));
		Application::standardShaderText->BindMat4("projection", Screen::GenerateOrthographicMatrix());
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(PrimitiveShapes::textQuadVAO);

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = labelFont->characters[*c];

			float xpos = x + ch.bearing.x * scale;
			float ypos = y + (ch.size.y - ch.bearing.y) * scale;

			float w = ch.size.x * scale;
			float h = ch.size.y * scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos - h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos - h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos - h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.textureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, PrimitiveShapes::textQuadVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.advance >> 6)* scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}





	//---------------------------------------------------------------------------//

	void UISystem::Update()
	{
		for (int i = 0; i < uiElements.size(); i++)
		{
			uiElements.at(i)->OnUpdate();
		}
	}
	void UISystem::Render()
	{
		glDisable(GL_DEPTH_TEST);

		for (int i = 0; i <= maxLayers; i++)
		{
			for (int j = 0; j < uiElements.size(); j++)
			{
				if (uiElements.at(j)->elementRect->layer == i)
				{
					uiElements.at(j)->OnRender();
				}
			}
		}

		glEnable(GL_DEPTH_TEST);
	}
}