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
		/**
		*Stores the parent UI rect.
		*/
		std::shared_ptr<UIRect> parentRect;
		/**
		*Stores the layer of the UI rect.
		*/
		unsigned int layer = 0;
		/**
		*Stores the position at the top left of the rect.
		*/
		glm::vec2 screenPosition = glm::vec2(0,0);
		/**
		*Stores how tall and wide the rect is from the origin point screenPosition.
		*/
		glm::vec2 rectScale = glm::vec2(0, 0);

		UIRect();
		UIRect(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _rectScale);

		/**
		*Returns the screen rect matrix.
		*/
		glm::mat4 GetUIMatrix();
		/**
		*Used to determine if the mouse is in the screen rect.
		*/
		bool IsMouseInRect();
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
		UIBox(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _scale);
		/**
		*Initializes a UI box with a screen rect and a base texture.
		*/
		UIBox(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _scale, std::string _baseTextureLoc);
		/**
		*Initializes a UI box with a screen rect and a base texture and hover texture.
		*/
		UIBox(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _scale, std::string _baseTextureLoc, std::string _hoverTextureLoc);

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

		bool pressed = false;

	public:
		std::shared_ptr<Texture> baseTexture, hoverTexture, clickedTexture;
		/**
		*Initializes a button with a screen position but no textures.
		*/
		UIButton(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _scale);
		/**
		*Initializes a button with a screen position and textures.
		*/
		UIButton(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _scale, std::string _baseTextureLoc, std::string _hoverTextureLoc, std::string _clickedTextureLoc);

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
	*Renders text onto the screen as a UI element.
	*/
	struct UILabel : public UIElement
	{
		std::shared_ptr<Font> labelFont;
		std::string text;
		glm::vec3 colour = glm::vec3(1.0f, 0.0f, 0.0f);
		float scale = 1.0f;

		UILabel(unsigned int _layer, glm::vec2 _screenPos, float _labelScale, std::string _labelText, glm::vec3 _textColour, std::shared_ptr<Font> _font);
		/**
		*Renders the text onto the screen.
		*/
		void OnRender();
	};
	/**
	*Stores the relevant information for a toggle tick box.
	*/
	struct UIToggle : public UIElement
	{
		bool toggle = false;
		std::shared_ptr<Texture> baseTexture, toggledTexture;

		UIToggle(unsigned int _layer, bool _startingValue, glm::vec2 _screenPos, glm::vec2 _rectScale, std::string _baseTextureLoc, std::string _toggleTextureLoc);

		void OnUpdate();
		void OnRender();
	};
	/**
	*Stores the relevant information for a slider.
	*/
	struct UISlider : public UIElement
	{
	private:

		std::shared_ptr<Texture> sliderTexture, handleTexture;
		std::shared_ptr<UIRect> handleRect;

		bool currentlyDragged = false;

	public:

		float maxValue = 0, currentValue = 0;
		float currentPercentage = 0;

		UISlider(unsigned int _layer, float _startingValue, float _maxValue, glm::vec2 _screenPos, glm::vec2 _rectScale, std::string _baseTextureLoc, std::string _sliderHandleTexture);

		void OnUpdate();
		void OnRender();
	};
	/**
	*Stores a list of UI elements as keeps them together as a group.
	*/
	struct UIWindow : UIElement
	{

	private:

		int maxLayers = 0;
		std::shared_ptr<Texture> windowTexture;
		bool currentlyDragged = false;
		std::vector<std::shared_ptr<UIElement>> uiElements;

	public:

		/**
		*Determines whether the window can be moved around the screen.
		*/
		bool draggable = false;

		/**
		*Initializes the UI window with parameters.
		*/
		UIWindow(unsigned int _layer, glm::vec2 _screenPos, glm::vec2 _scale, bool _canDrag, std::string _textureLoc);

		template<typename T>
		/**
		*Adds a UI element to the window without any parameters
		*/
		std::shared_ptr<T> AddUIElement()
		{
			std::shared_ptr<T> element = std::make_shared<T>();
			element->elementRect->parentRect = elementRect;
			uiElements.push_back(element);

			return element;
		}
		template<typename T, typename ... Args>
		/**
		*Adds a UI element to the window with parameters
		*/
		std::shared_ptr<T> AddUIElement(Args&&... _args)
		{
			std::shared_ptr<T> element = std::make_shared<T>(std::forward<Args>(_args)...);
			element->elementRect->parentRect = elementRect;
			uiElements.push_back(element);

			if (element->elementRect->layer > maxLayers)
			{
				maxLayers = element->elementRect->layer;
			}

			return element;
		}

		/**
		*Updates the UI window group
		*/
		void OnUpdate();
		/**
		*Renders the UI window group
		*/
		void OnRender();
	};


	/**
	*User written user interfaces can inherit from this class.
	*/
	struct UISystem
	{
	private:

		/**
		*Determines the max amount of layers in the UI system.
		*/
		int maxLayers = 0;

	public:

		/**
		*Determines whether the UI system is active. When false, updates, event handling and rendering is disabled.
		*/
		bool active = true;
		/**
		*Stores all the UI system elements.
		*/
		std::vector<std::shared_ptr<UIElement>> uiElements;

		template<typename T>
		/**
		*Adds a UI element to the system without any parameters
		*/
		std::shared_ptr<T> AddUIElement()
		{
			std::shared_ptr<T> element = std::make_shared<T>();
			uiElements.push_back(element);

			return element;
		}

		template<typename T, typename ... Args>
		/**
		*Adds a UI element to the system with parameters
		*/
		std::shared_ptr<T> AddUIElement(Args&&... _args)
		{
			std::shared_ptr<T> element = std::make_shared<T>(std::forward<Args>(_args)...);
			uiElements.push_back(element);

			if (element->elementRect->layer > maxLayers)
			{
				maxLayers = element->elementRect->layer;
			}

			return element;
		}

		/**
		*This can be used to initialize required UI elements.
		*/
		virtual void InitializeUI() {};
		/**
		*This can be used to handle what happens when UI elements are interacted with.
		*/
		virtual void HandleEvents() {};

		/**
		*Updates all the UI elements.
		*/
		void Update();
		/**
		*Renders all the UI elements.
		*/
		void Render();
	};
}

#endif