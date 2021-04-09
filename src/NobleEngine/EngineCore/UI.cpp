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

		glm::vec2 uiPosition = screenPosition;
		if (parentRect)
		{
			uiPosition = parentRect->screenPosition + screenPosition;
		}

		uiMat = glm::translate(uiMat, glm::vec3(uiPosition, 0.0f));
		uiMat = glm::scale(uiMat, glm::vec3(rectScale, 1.0f));

		return uiMat;
	}

	bool UIRect::IsMouseInRect()
	{
		int xMousePos = InputManager::mouseX;
		int yMousePos = InputManager::mouseY;

		glm::vec2 uiPosition = screenPosition;
		if (parentRect)
		{
			uiPosition = parentRect->screenPosition + screenPosition;
		}

		if (xMousePos >= uiPosition.x && xMousePos <= uiPosition.x + rectScale.x)
		{
			if (yMousePos >= uiPosition.y && yMousePos <= uiPosition.y + rectScale.y)
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

		glActiveTexture(GL_TEXTURE0);
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

		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error in Box Rendering!! Error Code: " << errorCode << std::endl;
		}
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

		glActiveTexture(GL_TEXTURE0);
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

		if (glGetError() != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error in Button Rendering!!" << std::endl;
		}
	}

	bool UIButton::ClickedOn()
	{
		return pressed;
	}

	//---------------------------------------------------------------------------//

	UILabel::UILabel(unsigned int layer, glm::vec2 screenPos, float labelScale, std::string labelText, glm::vec3 textColour, std::shared_ptr<Font> font)
	{
		elementRect = std::make_shared<UIRect>(layer, screenPos, glm::vec2(1.0, 1.0));
		text = labelText;
		colour = textColour;
		scale = labelScale;

		labelFont = font;
	}
	void UILabel::OnRender()
	{
		float x = elementRect->screenPosition.x;
		float y = elementRect->screenPosition.y + labelFont->fontPixelSize;

		// activate corresponding render state	
		Application::standardShaderText->UseProgram();
		Application::standardShaderText->BindVector3("textColor", colour);
		Application::standardShaderText->BindMat4("model", glm::scale(glm::mat4(1.0f), glm::vec3(elementRect->rectScale, 1.0f)));
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

		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error in Label Rendering!! Error Code: " << errorCode << std::endl;
		}
	}


	//---------------------------------------------------------------------------//

	UIToggle::UIToggle(unsigned int layer, bool startingValue, glm::vec2 screenPos, glm::vec2 rectScale, std::string baseTextureLoc, std::string toggleTextureLoc)
	{
		toggle = startingValue;
		elementRect = std::make_shared<UIRect>(layer, screenPos, rectScale);
		baseTexture = ResourceManager::LoadResource<Texture>(baseTextureLoc);
		toggledTexture = ResourceManager::LoadResource<Texture>(toggleTextureLoc);
	}

	void UIToggle::OnUpdate()
	{
		if (elementRect->IsMouseInRect())
		{
			if (InputManager::GetMouseButtonDown(0))
			{
				toggle = !toggle;
			}
		}
	}
	void UIToggle::OnRender()
	{
		Application::standardShaderUI->UseProgram();
		Application::standardShaderUI->BindMat4("u_UIPos", elementRect->GetUIMatrix());
		Application::standardShaderUI->BindMat4("u_Ortho", Screen::GenerateOrthographicMatrix());

		glActiveTexture(GL_TEXTURE0);
		if (!toggle)
		{
			if (baseTexture)
			{
				glBindTexture(GL_TEXTURE_2D, baseTexture->textureID);
			}
		}
		else
		{
			if (toggledTexture)
			{
				glBindTexture(GL_TEXTURE_2D, toggledTexture->textureID);
			}
		}
		glBindVertexArray(PrimitiveShapes::quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);

		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error in Toggle Rendering!! Error Code: " << errorCode << std::endl;
		}
	}

	//---------------------------------------------------------------------------//

	UISlider::UISlider(unsigned int layer, float startingValue, float maximumValue, glm::vec2 screenPos, glm::vec2 rectScale, std::string baseTextureLoc, std::string sliderHandleTexture)
	{
		elementRect = std::make_shared<UIRect>(layer, screenPos, rectScale);
		handleRect = std::make_shared<UIRect>(layer + 1, glm::vec2(screenPos.x, screenPos.y), glm::vec2(rectScale.y, rectScale.y));

		currentValue = startingValue;
		maxValue = maximumValue;

		sliderTexture = ResourceManager::LoadResource<Texture>(baseTextureLoc);
		handleTexture = ResourceManager::LoadResource<Texture>(sliderHandleTexture);
	}

	void UISlider::OnUpdate()
	{
		float minPos = elementRect->screenPosition.x;
		float maxPos = elementRect->screenPosition.x + elementRect->rectScale.x - handleRect->rectScale.x;

		float percentageValue = ((minPos + maxPos) / 100);
		currentPercentage = ((handleRect->screenPosition.x) / percentageValue) / 100;

		if (!currentlyDragged)
		{
			if (handleRect->IsMouseInRect() && elementRect->IsMouseInRect())
			{
				if (InputManager::GetMouseButton(0))
				{
					currentlyDragged = true;
				}
			}
		}
		else
		{
			handleRect->screenPosition.x = InputManager::mouseX - (handleRect->rectScale.x / 2);
			if (!InputManager::GetMouseButton(0))
			{
				currentlyDragged = false;
			}
		}

		if (handleRect->screenPosition.x <= minPos)
		{
			handleRect->screenPosition.x = minPos;
			currentPercentage = 0;
		}
		if (handleRect->screenPosition.x + handleRect->rectScale.x >= elementRect->screenPosition.x + elementRect->rectScale.x)
		{
			handleRect->screenPosition.x = maxPos;
			currentPercentage = 1;
		}

		currentValue = (maxValue * currentPercentage);
	}
	void UISlider::OnRender()
	{
		Application::standardShaderUI->UseProgram();
		Application::standardShaderUI->BindMat4("u_UIPos", elementRect->GetUIMatrix());
		Application::standardShaderUI->BindMat4("u_Ortho", Screen::GenerateOrthographicMatrix());

		glActiveTexture(GL_TEXTURE0);
		if (sliderTexture)
		{
			glBindTexture(GL_TEXTURE_2D, sliderTexture->textureID);
		}
		glBindVertexArray(PrimitiveShapes::quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		Application::standardShaderUI->BindMat4("u_UIPos", handleRect->GetUIMatrix());
		if (handleTexture)
		{
			glBindTexture(GL_TEXTURE_2D, handleTexture->textureID);
		}
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
		glUseProgram(0);

		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error in Slider Rendering!! Error Code: " << errorCode << std::endl;
		}
	}

	//---------------------------------------------------------------------------//

	UIWindow::UIWindow(unsigned int layer, glm::vec2 screenPos, glm::vec2 scale, bool canDrag, std::string textureLoc)
	{
		maxLayers = 0;
		draggable = canDrag;

		elementRect = std::make_shared<UIRect>(layer, screenPos, scale);
		windowTexture = ResourceManager::LoadResource<Texture>(textureLoc);
	}

	void UIWindow::OnUpdate()
	{
		if (draggable)
		{
			bool canDrag = true;
			for (int i = 0; i < uiElements.size(); i++)
			{
				if (uiElements.at(i)->elementRect->IsMouseInRect())
				{
					canDrag = false;
					break;
				}
			}

			if (canDrag)
			{
				if (!currentlyDragged)
				{
					if (elementRect->IsMouseInRect())
					{
						if (InputManager::GetMouseButton(0))
						{
							currentlyDragged = true;
						}
					}
				}
				else
				{
					elementRect->screenPosition = glm::vec2(InputManager::mouseX - (elementRect->rectScale.x / 2), InputManager::mouseY - (elementRect->rectScale.y / 2));
					if (!InputManager::GetMouseButton(0))
					{
						currentlyDragged = false;
					}
				}
			}
		}

		for (int i = 0; i < uiElements.size(); i++)
		{
			uiElements.at(i)->OnUpdate();
		}
	}
	void UIWindow::OnRender()
	{
		Application::standardShaderUI->UseProgram();
		Application::standardShaderUI->BindMat4("u_UIPos", elementRect->GetUIMatrix());
		Application::standardShaderUI->BindMat4("u_Ortho", Screen::GenerateOrthographicMatrix());

		glActiveTexture(GL_TEXTURE0);
		if (windowTexture)
		{
			glBindTexture(GL_TEXTURE_2D, windowTexture->textureID);
		}
		glBindVertexArray(PrimitiveShapes::quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);

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

		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error in Window Rendering!! Error Code: " << errorCode << std::endl;
		}
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
		if (glGetError() != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error in UI Rendering!!" << std::endl;
		}

		glEnable(GL_DEPTH_TEST);
	}
}