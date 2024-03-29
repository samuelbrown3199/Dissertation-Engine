#include "Screen.h"

namespace NobleEngine
{
	int Screen::screenWidth = 0;
	int Screen::screenHeight = 0;
	SDL_Window* Screen::window;
	SDL_GLContext Screen::glContext;

	float Screen::nearPlane = 0.1f;
	float Screen::farPlane = 1000.0f;
	float Screen::fieldOfView = 90.0f;

	Screen::Screen(int width, int height, float near, float far, std::string windowName)
	{
		screenWidth = width;
		screenHeight = height;
		nearPlane = near;
		farPlane = far;

		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		
		glContext = SDL_GL_CreateContext(window);
		/*if (!SDL_GL_CreateContext(window))
		{
			std::cout << "Screen failed to create window!" << std::endl;
			throw std::exception();
		}*/
	}

	SDL_Window* Screen::GetWindow()
	{
		return window;
	}

	int Screen::GetScreenWidth()
	{
		return screenWidth;
	}

	int Screen::GetScreenHeight()
	{
		return screenHeight;
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

	glm::mat4 Screen::GenerateOrthographicMatrix()
	{
		glm::mat4 orthoMatrix = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f, 0.0f, farPlane);
		return orthoMatrix;
	}

	void Screen::SwapWindow()
	{
		SDL_GL_SwapWindow(window);
	}
}