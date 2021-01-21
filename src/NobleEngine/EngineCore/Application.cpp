#include "Application.h"

#include "Screen.h"
#include "../Components/Camera.h"
#include "ResourceManager.h"
#include "PhysicsWorld.h"
#include "System.h"
#include "Entity.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "InputManager.h"

#include "../Systems/TransformSystem.h"
#include "../Systems/MeshRendererSystem.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/PhysicsBodySystem.h"
#include "../Systems/AudioSourceSystem.h"
#include "../Systems/AudioListenerSystem.h"
#include "../Systems/LightSystem.h"

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
		app->resourceManager = std::make_shared<ResourceManager>();
		app->physicsWorld = PhysicsWorld::CreatePhysicsWorld();

		std::shared_ptr<Shader> vertexShader = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard.vs");
		std::shared_ptr<Shader> fragmentShader = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard.fs");

		app->standardShader = std::make_shared<ShaderProgram>(app);
		app->standardShader->BindShader(vertexShader, GL_VERTEX_SHADER);
		app->standardShader->BindShader(fragmentShader, GL_FRAGMENT_SHADER);
		app->standardShader->LinkShaderProgram();

		return app;
	}

	void Application::MainLoop()
	{
		BindCoreSystems();

		SDL_Event e = { 0 };
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		
		glClearColor(0.0f, 0.45f, 0.45f, 1.0f);

		Uint32 frameStart;

		while (loop)
		{
			frameStart = SDL_GetTicks();

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					loop = false;
				}
			}
			screen->UpdateScreenSize();
			InputManager::GetMousePosition();

			for (size_t sys = 0; sys < systems.size(); sys++) //handles system updates
			{
				systems.at(sys)->Update();
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (size_t sys = 0; sys < systems.size(); sys++) //handles system rendering
			{
				systems.at(sys)->Render();
			}

			SDL_GL_SwapWindow(screen->GetWindow());

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
			ResourceManager::UnloadUnusedResources();

			double frameTime = SDL_GetTicks() - frameStart;
			double fps = 1000.0f / frameTime;
			double deltaT = 1.0f / fps;
			physicsWorld->StepSimulation(deltaT);

			std::cout << "FPS: " << fps  << "	delta t: " << deltaT << "	frametime: " << frameTime << std::endl;
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
		BindSystem<TransformSystem>(false, true, false);
		BindSystem<PhysicsBodySystem>(false, true, false);
		BindSystem<CameraSystem>(false, true, false);
		BindSystem<AudioListenerSystem>(false, true, false);
		BindSystem<AudioSourceSystem>(false, true, false);
		BindSystem<LightSystem>(false, false, true);
		BindSystem<MeshRendererSystem>(true, false, true);
	}

	void Application::RemoveEntity(int ID)
	{
		entities.at(ID)->RemoveAllComponents();
		entities.at(ID).reset();
		availableIDs.push_back(ID);
	}
}