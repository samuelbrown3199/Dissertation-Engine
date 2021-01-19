#include "Screen.h"

namespace NobleEngine
{
	Screen::Screen(int width, int height, float near, float far, std::string windowName)
	{
		screenWidth = width;
		screenHeight = height;
		nearPlane = near;
		farPlane = far;

		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		if (!SDL_GL_CreateContext(window))
		{
			std::cout << "Screen failed to create window!" << std::endl;
			throw std::exception();
		}
	}

	SDL_Window* Screen::GetWindow()
	{
		return window;
	}

	void Screen::UpdateScreenSize()
	{
		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		screenWidth = w;
		screenHeight = h;
		glViewport(0, 0, screenWidth, screenHeight);
	}

	glm::mat4 Screen::GenerateProjectionMatrix()
	{
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(fieldOfView), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);
		return projectionMatrix;
	}
}