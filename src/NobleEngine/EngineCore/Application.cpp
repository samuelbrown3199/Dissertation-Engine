#include "Application.h"

#include "Screen.h"
#include "ThreadingManager.h"
#include "ResourceManager.h"
#include "PhysicsWorld.h"
#include "System.h"
#include "Entity.h"
#include "InputManager.h"

#include "../Systems/TransformSystem.h"
#include "../Systems/MeshRendererSystem.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/PhysicsBodySystem.h"
#include "../Systems/AudioSourceSystem.h"
#include "../Systems/AudioListenerSystem.h"
#include "../Systems/LightSystem.h"
#include "../Systems/SpriteRendererSystem.h"

#include "../Components/Camera.h"

#include "../ResourceManagement/ShaderProgram.h"

namespace NobleEngine
{
	std::weak_ptr<Application> Application::self;

	std::shared_ptr<ResourceManager> Application::resourceManager;
	std::vector<std::shared_ptr<SystemBase>> Application::systems;

	std::vector<std::shared_ptr<Entity>> Application::deletionEntities;
	std::vector<std::shared_ptr<Entity>> Application::entities;
	std::vector<int> Application::availableIDs;
	std::shared_ptr<PhysicsWorld> Application::physicsWorld;

	std::shared_ptr<ShaderProgram> Application::standardShader;
	std::shared_ptr<ShaderProgram> Application::standardShader2D;
	std::shared_ptr<Camera> Application::activeCam;
	std::shared_ptr<Screen> Application::screen;

	std::shared_ptr<Application> Application::InitializeEngine(std::string windowName, int windowWidth, int windowHeight)
	{
		std::shared_ptr<Application> app(new Application());
		Application::self = app;
		app->screen = std::make_shared<Screen>(windowWidth, windowHeight, 0.1, 1000, windowName);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Application failed to initialize glew!" << std::endl;
			throw std::exception();
		}
		app->audioDevice = alcOpenDevice(NULL);
		if (!app->audioDevice)
		{
			std::cout << "Application failed to initialize audio device!" << std::endl;
		}
		app->audioContext = alcCreateContext(app->audioDevice, NULL);
		if (!app->audioContext)
		{
			std::cout << "Application failed to initialize audio context!" << std::endl;
			alcCloseDevice(app->audioDevice);
		}
		if (!alcMakeContextCurrent(app->audioContext))
		{
			std::cout << "Application failed to assign audio context!" << std::endl;
			alcDestroyContext(app->audioContext);
			alcCloseDevice(app->audioDevice);
		}
		ThreadingManager::SetupMaxThreads();
		app->resourceManager = std::make_shared<ResourceManager>();
		app->physicsWorld = PhysicsWorld::CreatePhysicsWorld();

		std::shared_ptr<Shader> vertexShader = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard.vs");
		std::shared_ptr<Shader> fragmentShader = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard.fs");
		std::shared_ptr<Shader> vertexShader2D = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard2D.vs");
		std::shared_ptr<Shader> fragmentShader2D = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard2D.fs");

		app->standardShader = std::make_shared<ShaderProgram>(app);
		app->standardShader->BindShader(vertexShader, GL_VERTEX_SHADER);
		app->standardShader->BindShader(fragmentShader, GL_FRAGMENT_SHADER);
		app->standardShader->LinkShaderProgram(app->standardShader);

		app->standardShader2D = std::make_shared<ShaderProgram>(app);
		app->standardShader2D->BindShader(vertexShader2D, GL_VERTEX_SHADER);
		app->standardShader2D->BindShader(fragmentShader2D, GL_FRAGMENT_SHADER);
		app->standardShader2D->LinkShaderProgram(app->standardShader2D);

		PrimativeShapes::SetupPrimitiveShapes();

		return app;
	}

	void Application::MainLoop()
	{
		BindCoreSystems();

		SDL_Event e = { 0 };
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		
		glClearColor(0.0f, 0.45f, 0.45f, 1.0f);

		Uint32 frameStart, renderStart, updateStart, physicsStart;
		double frameTime = 0;
		double fps = 0;
		double deltaT = 0;

		const int avgFrameRateCount = 10;
		std::vector<int> framerateList;
		int currentFrameCount = 0;
		double avgFPS = 0;

		while (loop)
		{
			frameStart = SDL_GetTicks();
			double updateTime = 0;
			double renderTime = 0;
			double physicsTime = 0;

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					loop = false;
				}
			}
			screen->UpdateScreenSize();
			InputManager::GetMousePosition();

			std::shared_ptr<std::thread> physicsThread = ThreadingManager::CreateThread(&PhysicsWorld::StepSimulation, physicsWorld, deltaT); //Update the physics world simulation.

			updateStart = SDL_GetTicks();
			for (size_t sys = 0; sys < systems.size(); sys++) //handles system updates
			{
				systems.at(sys)->Update();
			}
			updateTime = SDL_GetTicks() - updateStart;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderStart = SDL_GetTicks();
			for (size_t sys = 0; sys < systems.size(); sys++) //handles system rendering
			{
				systems.at(sys)->Render();
			}
			renderTime = SDL_GetTicks() - renderStart;

			SDL_GL_SwapWindow(screen->GetWindow());

			physicsStart = SDL_GetTicks();
			ThreadingManager::JoinThread(physicsThread);
			physicsTime = SDL_GetTicks() - physicsStart;

			std::vector<std::shared_ptr<Entity>>::iterator deleter;
			for (deleter = deletionEntities.end(); deleter != deletionEntities.begin(); deleter--)
			{
				std::shared_ptr<Entity> entity = *deleter;
				deletionEntities.pop_back();
				RemoveEntity(entity->entityID);
			}
			for (size_t sys = 0; sys < systems.size(); sys++) //handles system cleanup
			{
				systems.at(sys)->ClearUnneededComponents();
			}
			ThreadingManager::CleanupLooseThreads();
			ResourceManager::UnloadUnusedResources();

			frameTime = SDL_GetTicks() - frameStart;
			fps = 1000.0f / frameTime;
			deltaT = 1.0f / fps;
			framerateList.push_back(fps);
			currentFrameCount++;

			if (avgFrameRateCount == currentFrameCount)
			{
				avgFPS = 0;
				for (int i = 0; i < framerateList.size(); i++)
				{
					avgFPS += framerateList.at(i);
				}
				framerateList.clear();
				avgFPS /= avgFrameRateCount;
				currentFrameCount = 0;
			}

			std::cout << "AVG FPS: " << avgFPS << "	Frame Time: " << frameTime << "	Update Time: " << updateTime << "	Render Time: " << renderTime << "	Physics thread join Time: " << physicsTime << std::endl;
		}

		physicsWorld->CleanupPhysicsWorld();
	}

	std::shared_ptr<Entity> Application::CreateEntity()
	{
		std::shared_ptr<Entity> en = std::make_shared<Entity>();
		if (availableIDs.size() > 0)
		{
			int id = availableIDs.at(0);
			std::vector<int>::iterator it = availableIDs.begin();
			availableIDs.erase(it);

			en->entityID = id;
			en->self = en;
			entities.at(id) = en;
			return en;
		}
		en->entityID = entities.size();
		en->self = en;
		entities.push_back(en);
		return en;
	}
	std::shared_ptr<Entity> Application::CreateEntity(std::string tag)
	{
		std::shared_ptr<Entity> en = std::make_shared<Entity>();
		if (availableIDs.size() > 0)
		{
			int id = availableIDs.at(0);
			std::vector<int>::iterator it = availableIDs.begin();
			availableIDs.erase(it);

			en->entityID = id;
			en->tag = tag;
			en->self = en;
			entities.at(id) = en;
			return en;
		}
		en->entityID = entities.size();
		en->tag = tag;
		en->self = en;
		entities.push_back(en);

		return en;
	}

	std::shared_ptr<Entity> Application::GetEntity(int ID)
	{
		for (size_t en = 0; en < entities.size(); en++)
		{
			if (entities.at(en))
			{
				if (entities.at(en)->entityID == ID)
				{
					return entities.at(en);
				}
			}
		}

		std::cout << "Entity could not be found with ID: " << ID << std::endl;
		throw std::exception();
	}

	std::shared_ptr<ResourceManager> Application::GetResourceManager()
	{
		return resourceManager;
	}

	std::shared_ptr<PhysicsWorld> Application::GetPhysicsWorld()
	{
		return physicsWorld;
	}

	void Application::BindCoreSystems()
	{
		BindSystem<TransformSystem>(true, false, 5000);
		BindSystem<PhysicsBodySystem>(true, false, 5000);
		BindSystem<CameraSystem>(true, false);
		BindSystem<AudioListenerSystem>(true, false);
		BindSystem<AudioSourceSystem>(true, false);
		BindSystem<LightSystem>(false, true);
		BindSystem<MeshRendererSystem>(false, true);
		BindSystem<SpriteRendererSystem>(false, true);
	}

	void Application::RemoveEntity(int ID)
	{
		entities.at(ID)->RemoveAllComponents();
		entities.at(ID).reset();
		availableIDs.push_back(ID);
	}
}