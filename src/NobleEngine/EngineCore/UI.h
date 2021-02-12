#pragma once
#ifndef UI_H_
#define UI_H_

#include <iostream>

#include <GL/glew.h>
#include<glm/glm.hpp>

#include "Application.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Screen.h"

#include "../ResourceManagement/ShaderProgram.h"
#include "../ResourceManagement/Model.h"
#include "../ResourceManagement/Texture.h"
#include "../ResourceManagement/Font.h"

namespace NobleEngine
{
	/**
	*Stores the screen position and scale for UI elements on the screen.
	*/
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

		bool IsMouseInRect()
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
	};
	/**
	*UI element types inherit from this base class.
	*/
	struct UIElement
	{
		std::shared_ptr<UIRect> elementRect;

		virtual void OnUpdate() {};
		virtual void OnRender() {};
	};

	/**
	*Stores the relevant information for a UI box.
	*/
	struct UIBox : public UIElement
	{
		std::shared_ptr<Texture> baseTexture, hoverTexture;
		/**
		*Initializes a UI box with a screen rect.
		*/
		UIBox(glm::vec2 screenPos, glm::vec2 scale);
		/**
		*Initializes a UI box with a screen rect and a base texture.
		*/
		UIBox(glm::vec2 screenPos, glm::vec2 scale, std::string baseTextureLoc);
		/**
		*Initializes a UI box with a screen rect and a base texture and hover texture.
		*/
		UIBox(glm::vec2 screenPos, glm::vec2 scale, std::string baseTextureLoc, std::string hoverTextureLoc);

		/**
		*Renders a UI box onto the screen.
		*/
		void OnRender();
	};

	/**
	*Stores the relevant information for a UI button. When clicked, it can call a function.
	*/
	struct UIButton : public UIElement
	{
	private:

		bool pressed = false, oldPressed;

	public:
		std::shared_ptr<Texture> baseTexture, hoverTexture, clickedTexture;
		/**
		*Initializes a button with a screen position but no textures.
		*/
		UIButton(glm::vec2 screenPos, glm::vec2 scale);
		/**
		*Initializes a button with a screen position and textures.
		*/
		UIButton(glm::vec2 screenPos, glm::vec2 scale, std::string baseTextureLoc, std::string hoverTextureLoc, std::string clickedTextureLoc);

		/**
		*Determines whether the button is currently clicked on this frame.
		*/
		void OnUpdate();
		/**
		*Renders a UI button onto the screen.
		*/
		void OnRender();
		/**
		*Returns whether the button is currently clicked on.
		*/
		bool ClickedOn();
	};

	/**
	*Renders text onto the screen.
	*/
	struct UILabel : public UIElement
	{
		std::shared_ptr<Font> labelFont;
		std::string text;
		glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
		float scale = 1.0f;

		UILabel(glm::vec2 screenPos, glm::vec2 scale);
		/**
		*Renders the text onto the screen.
		*/
		void OnRender();
	};
}

#endif