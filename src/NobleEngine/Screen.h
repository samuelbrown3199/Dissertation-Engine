#include<glm/glm.hpp>
#include <glm/ext.hpp>

namespace NobleEngine
{
	struct Screen
	{
		int screenWidth, screenHeight;
		float nearPlane = 0.1f, farPlane = 100.0f;

		Screen(int width, int height);
		glm::mat4 GenerateProjectionMatrix();
	};
}