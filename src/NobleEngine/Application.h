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
	class Entity;

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
		*Creates an entity with no tag.
		*/
		std::shared_ptr<Entity> CreateEntity();
		/**
		*Creates an entity with the passed in tag.
		*/
		std::shared_ptr<Entity> CreateEntity(std::string tag);
		/**
		*Binds the system to the engine core for use in game functionality;
		*/
		template<typename T>
		void BindSystem(std::shared_ptr<T> system)
		{
			systems.push_back(system);
		}
		/**
		*Gets a bound system of the passed type.
		*/
		template<typename T>
		std::shared_ptr<T> GetSystem()
		{
			std::shared_ptr sys;
			for (size_t s = 0; s < systems.size(); s++)
			{
				sys = std::dynamic_pointer_cast<T>(systems.at(s));
				if (!sys) continue;

				return sys;
			}
		}

	private:

		std::weak_ptr<Application> self;
		SDL_Window* window;
		bool loop = true;
		/**
		*Stores systems for use within the game engine.
		*/
		std::vector<std::shared_ptr<System>> systems;
		/**
		*Stores entities for use within the game engine.
		*/
		std::vector<std::shared_ptr<Entity>> entities;
		/**
		*Binds core systems so the engine user doesnt have to.
		*/
		void BindCoreSystems();
	};
}