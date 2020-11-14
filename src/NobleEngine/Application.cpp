#include "Application.h"
#include "System.h"

namespace NobleEngine
{
	std::shared_ptr<Application> Application::InitializeEngine(std::string windowName)
	{
		std::shared_ptr<Application> app(new Application());
		app->self = app;

		app->window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 900, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		if (!SDL_GL_CreateContext(app->window))
		{
			std::cout << "Application failed to create window!" << std::endl;
			throw std::exception();
		}
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Application failed to initialize glew!" << std::endl;
			throw std::exception();
		}

		return app;
	}

	void Application::MainLoop()
	{
		SDL_Event e = { 0 };

		while (loop)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					loop = false;
				}
			}

			for (size_t sys = 0; sys < systems.size(); sys++)
			{
				systems.at(sys)->Update();
			}
		}
	}
}