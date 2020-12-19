#include "Screen.h"

namespace NobleEngine
{
	Screen::Screen(int width, int height)
	{
		screenWidth = width;
		screenHeight = height;
	}

	glm::mat4 Screen::GenerateProjectionMatrix()
	{
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);
		return projectionMatrix;
	}
}