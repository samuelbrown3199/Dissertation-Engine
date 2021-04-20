#pragma once
#ifndef SCREEN_H_
#define SCREEN_H_

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
		static int screenWidth;
		/**
		*Stores the screen height.
		*/
		static int screenHeight;
		/**
		*Stores a pointer to the application window.
		*/
		static SDL_Window* window;
		/**
		*Stores the OpenGL context.
		*/
		static SDL_GLContext glContext;

	public:
		/**
		*Stores the near plane clipping limit.
		*/
		static float nearPlane;
		/**
		*Stores the far plane clipping limit.
		*/
		static float farPlane;
		/**
		*Stores the field of view value.
		*/
		static float fieldOfView;
		/**
		*Initializes a screen object.
		*/
		Screen(int _width, int _height, float _near, float _far, std::string _windowName);
		/**
		*Returns the SDL window.
		*/
		static SDL_Window* GetWindow();
		/**
		*Returns the screen width.
		*/
		static int GetScreenWidth();
		/**
		*Returns the screen height.
		*/
		static int GetScreenHeight();
		/**
		*Updates the screen size and gl viewport.
		*/
		static void UpdateScreenSize();
		/**
		*Generates a projection matrix with the screen information.
		*/
		static glm::mat4 GenerateProjectionMatrix();
		/**
		*Generates a orthographic matrix with the screen information.
		*/
		static glm::mat4 GenerateOrthographicMatrix();

		static void SwapWindow();
	};
}

#endif