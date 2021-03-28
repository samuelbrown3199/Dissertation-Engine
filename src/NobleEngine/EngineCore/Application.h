#pragma once
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <thread>

#include <SDL.h>
#include <GL/glew.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace NobleEngine
{
	struct Screen;
	struct PerformanceStats;
	struct ResourceManager;
	struct PhysicsWorld;
	struct SystemBase;
	struct Entity;
	struct ShaderProgram;
	struct UISystem;
	struct Scene;

	struct Camera;

	/**
	*Application is the core of the engine. This will initialize and handle the main loop of the engine. This also stores a list of entities and systems. These will be used to create functionality of the engine.
	*/
	class Application
	{

	public:
		/**
		*Determines whether the main engine loop should run.
		*/
		static bool loop;
		/**
		*Stores the engines performance stats.
		*/
		static PerformanceStats performanceStats;
		/**
		*Stores the currently active scene.
		*/
		static std::shared_ptr<Scene> activeScene;
		/**
		*Stores a weak pointer to itself.
		*/
		static std::weak_ptr<Application> self;
		static std::shared_ptr<Camera> activeCam;
		/**
		*Stores screen data.
		*/
		static std::shared_ptr<Screen> screen;
		/**
		*Stores an initialized free type library.
		*/
		static FT_Library fontLibrary;
		/**
		*Stores a list of entities marked for deletion.
		*/
		static std::vector<std::shared_ptr<Entity>> deletionEntities;
		/**
		*Stores the standard shader program built into the engine.
		*/
		static std::shared_ptr<ShaderProgram> standardShader;
		/**
		*Stores the standard 2D shader program built into the engine.
		*/
		static std::shared_ptr<ShaderProgram> standardShader2D;
		/**
		*Stores the standard UI shader program built into the engine.
		*/
		static std::shared_ptr<ShaderProgram> standardShaderUI;
		/**
		*Stores the standard text shader program built into the engine.
		*/
		static std::shared_ptr<ShaderProgram> standardShaderText;
		/**
		*Initializes the systems within the engine.
		*/
		static std::shared_ptr<Application> InitializeEngine(std::string _windowName, int _windowWidth, int _windowHeight);
		/**
		*Starts and manages the main engine loop.
		*/
		void MainLoop();
		/**
		*Creates a scene and adds it to the application scene list.
		*/
		static std::shared_ptr<Scene> CreateScene();
		/**
		*Changes the scene to the scene at index.
		*/
		static void ChangeScene(int index);
		/**
		*Creates an entity with no tag.
		*/
		static std::shared_ptr<Entity> CreateEntity();
		/**
		*Returns an entity with the ID passed through the parameter;
		*/
		static std::shared_ptr<Entity> GetEntity(int _ID);
		/**
		*Returns the resource manager.
		*/
		static std::shared_ptr<ResourceManager> GetResourceManager();
		/**
		*Returns the physics world simulation.
		*/
		static std::shared_ptr<PhysicsWorld> GetPhysicsWorld();
		/**
		*Binds the system to the engine core for use in game functionality. Only one of each system type can be bound at a time.
		*/
		template<typename T>
		static void BindSystem(bool _update, bool _render)
		{
			std::shared_ptr<T> temp;
			for (size_t sys = 0; sys < systems.size(); sys++)
			{
				temp = std::dynamic_pointer_cast<T>(systems.at(sys));
				if (temp)
				{
					std::cout << "System is already bound!!" << std::endl;
					return;
				}
			}

			std::shared_ptr<T> system = std::make_shared<T>();
			system->SetSystemUse(_update, _render);
			system->application = self;
			self.lock()->systems.push_back(system);
		}
		/**
		*Binds the system to the engine core for use in game functionality. Only one of each system type can be bound at a time. This sets it up with threading.
		*/
		template<typename T>
		static void BindSystem(bool _update, bool _render, int _amountOfComponentsPerThread)
		{
			std::shared_ptr<T> temp;
			for (size_t sys = 0; sys < systems.size(); sys++)
			{
				temp = std::dynamic_pointer_cast<T>(systems.at(sys));
				if (temp)
				{
					std::cout << "System is already bound!!" << std::endl; 
					return;
				}
			}

			std::shared_ptr<T> system = std::make_shared<T>();
			system->SetSystemUse(_update, _render);
			system->SetThreadingUse(_amountOfComponentsPerThread);
			system->application = self;
			self.lock()->systems.push_back(system);
		}
		/**
		*Gets a bound system of the passed type.
		*/
		template<typename T>
		static std::shared_ptr<T> GetSystem()
		{
			std::shared_ptr<T> sys;
			for (size_t s = 0; s < systems.size(); s++)
			{
				sys = std::dynamic_pointer_cast<T>(systems.at(s));
				if (!sys) continue;

				return sys;
			}
		}

		template<typename T>
		static std::shared_ptr<T> BindUISystem()
		{
			std::shared_ptr<T> sys = std::make_shared<T>();
			sys->InitializeUI();

			uiSystems.push_back(sys);
			return sys;
		}

	private:
		/**
		*Stores a pointer to the current audio device.
		*/
		ALCdevice* audioDevice;
		/**
		*Stores a pointer to the current audio context.
		*/
		ALCcontext* audioContext;
		/**
		*Stores the physics simulation world.
		*/
		static std::shared_ptr<PhysicsWorld> physicsWorld;
		/**
		*Stores a list of all scenes added to the application.
		*/
		static std::vector<std::shared_ptr<Scene>> scenes;
		/**
		*Stores systems for use within the game engine.
		*/
		static std::vector<std::shared_ptr<SystemBase>> systems;
		/**
		*Stores all the user interface systems.
		*/
		static std::vector <std::shared_ptr<UISystem>> uiSystems;
		/**
		*Stores entities for use within the game engine.
		*/
		static std::vector<std::shared_ptr<Entity>> entities;
		/**
		*Stores a list of available entity IDS.
		*/
		static std::vector<int> availableIDs;
		/**
		*Stores the resource manager.
		*/
		static std::shared_ptr<ResourceManager> resourceManager;
		/**
		*Binds core systems so the engine user doesnt have to.
		*/
		void BindCoreSystems();
		/**
		*Removes an entity with the passed ID parameter.
		*/
		void RemoveEntity(int _ID);
	};
}

#endif