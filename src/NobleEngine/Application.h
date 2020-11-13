#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>

#include <SDL.h>
#include <GL/glew.h>

namespace NobleEngine
{
	class Application
	{
	public:

		static std::shared_ptr<Application> InitializeEngine(std::string windowName);
		void MainLoop();

	private:

		std::weak_ptr<Application> self;
		SDL_Window* window;
		bool loop = true;
	};
}