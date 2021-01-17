#include <iostream>
#include <string>

#include<glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL.h>
#include <GL/glew.h>

namespace NobleEngine
{
	/**
	*Handles the window information and functionality.
	*/
	struct Screen
	{
	private:
		/**
		*Stores the screen Width.
		*/
		int screenWidth;
		/**
		*Stores the screen height.
		*/
		int screenHeight;
		/**
		*Stores a pointer to the application window.
		*/
		SDL_Window* window;

	public:
		/**
		*Stores the near plane clipping limit.
		*/
		float nearPlane = 0.1f;
		/**
		*Stores the far plane clipping limit.
		*/
		float farPlane = 1000.0f;
		/**
		*Stores the field of view value.
		*/
		float fieldOfView = 90.0f;
		/**
		*Initializes a screen object.
		*/
		Screen(int width, int height, float near, float far, std::string windowName);
		/**
		*Returns the SDL window.
		*/
		SDL_Window* GetWindow();
		/**
		*Updates the screen size and gl viewport.
		*/
		void UpdateScreenSize();
		/**
		*Generates a projection matrix with the screen information.
		*/
		glm::mat4 GenerateProjectionMatrix();
	};
}