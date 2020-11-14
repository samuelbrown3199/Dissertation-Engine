#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>

#include <SDL.h>
#include <GL/glew.h>

namespace NobleEngine
{
	class System;

	/**
	*Application is the core of the engine. This will initialize and handle the main loop of the engine.
	*/
	class Application
	{
	public:

		/**
		*Initializes the systems within the engine.
		*/
		static std::shared_ptr<Application> InitializeEngine(std::string windowName);

		/**
		*Starts and manages the main engine loop.
		*/
		void MainLoop();

		/**
		*Binds the system to the engine core for use in game functionality;
		*/
		template<typename T>
		void BindSystem(std::shared_ptr<T> system)
		{
			systems.push_back(system);
		}

	private:

		std::weak_ptr<Application> self;
		SDL_Window* window;
		bool loop = true;

		/**
		*Stores systems for use within the game engine.
		*/
		std::vector<std::shared_ptr<System>> systems;
	};
}