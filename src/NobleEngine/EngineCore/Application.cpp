#include "Application.h"

#include "Screen.h"
#include "PerformanceStats.h"
#include "ThreadingManager.h"
#include "ResourceManager.h"
#include "PhysicsWorld.h"
#include "System.h"
#include "Entity.h"
#include "InputManager.h"
#include "UI.h"
#include "Scene.h"

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
	std::vector <std::shared_ptr<UISystem>> Application::uiSystems;

	std::vector<std::shared_ptr<Entity>> Application::deletionEntities;
	std::vector<std::shared_ptr<Entity>> Application::entities;
	std::vector<int> Application::availableIDs;
	std::shared_ptr<PhysicsWorld> Application::physicsWorld;
	std::shared_ptr<Scene> Application::activeScene;
	std::vector<std::shared_ptr<Scene>> Application::scenes;

	std::shared_ptr<ShaderProgram> Application::standardShader;
	std::shared_ptr<ShaderProgram> Application::standardShader2D;
	std::shared_ptr<ShaderProgram> Application::standardShaderUI;
	std::shared_ptr<ShaderProgram> Application::standardShaderText;

	std::shared_ptr<Camera> Application::activeCam;
	std::shared_ptr<Screen> Application::screen;
	FT_Library Application::fontLibrary;
	PerformanceStats Application::performanceStats;

	bool Application::loop = true;

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
		if (FT_Init_FreeType(&app->fontLibrary))
		{
			std::cout << "Could not initialize FreeType Library!" << std::endl;
			throw std::exception();
		}
		ThreadingManager::SetupMaxThreads();
		app->resourceManager = std::make_shared<ResourceManager>();
		app->physicsWorld = PhysicsWorld::CreatePhysicsWorld();

		std::shared_ptr<Shader> vertexShader = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard.vs");
		std::shared_ptr<Shader> fragmentShader = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard.fs");
		std::shared_ptr<Shader> vertexShader2D = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard2D.vs");
		std::shared_ptr<Shader> fragmentShader2D = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\standard2D.fs");
		std::shared_ptr<Shader> vertexShaderUI = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\uiStandard.vs");
		std::shared_ptr<Shader> fragmentShaderUI = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\uiStandard.fs");
		std::shared_ptr<Shader> vertexShaderText = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\textStandard.vs");
		std::shared_ptr<Shader> fragmentShaderText = app->GetResourceManager()->LoadResource<Shader>("Resources\\Shaders\\textStandard.fs");

		app->standardShader = std::make_shared<ShaderProgram>(app);
		app->standardShader->BindShader(vertexShader, GL_VERTEX_SHADER);
		app->standardShader->BindShader(fragmentShader, GL_FRAGMENT_SHADER);
		app->standardShader->LinkShaderProgram(app->standardShader);

		app->standardShader2D = std::make_shared<ShaderProgram>(app);
		app->standardShader2D->BindShader(vertexShader2D, GL_VERTEX_SHADER);
		app->standardShader2D->BindShader(fragmentShader2D, GL_FRAGMENT_SHADER);
		app->standardShader2D->LinkShaderProgram(app->standardShader2D);

		app->standardShaderUI = std::make_shared<ShaderProgram>(app);
		app->standardShaderUI->BindShader(vertexShaderUI, GL_VERTEX_SHADER);
		app->standardShaderUI->BindShader(fragmentShaderUI, GL_FRAGMENT_SHADER);
		app->standardShaderUI->LinkShaderProgram(app->standardShaderUI);

		app->standardShaderText = std::make_shared<ShaderProgram>(app);
		app->standardShaderText->BindShader(vertexShaderText, GL_VERTEX_SHADER);
		app->standardShaderText->BindShader(fragmentShaderText, GL_FRAGMENT_SHADER);
		app->standardShaderText->LinkShaderProgram(app->standardShaderText);

		activeScene = CreateScene();
		PrimitiveShapes::SetupPrimitiveShapes();

		return app;
	}

	void Application::MainLoop()
	{
		BindCoreSystems();

		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glClearColor(0.0f, 0.45f, 0.45f, 1.0f);

		while (loop)
		{
			performanceStats.ResetPerformanceStats();

			InputManager::HandleGeneralInput();
			screen->UpdateScreenSize();

			std::shared_ptr<std::thread> physicsThread = ThreadingManager::CreateThread(&PhysicsWorld::StepSimulation, physicsWorld, performanceStats.deltaT); //Update the physics world simulation.

			performanceStats.updateStart = SDL_GetTicks();
			for (size_t sys = 0; sys < systems.size(); sys++) //handles system updates
			{
				systems.at(sys)->Update();
			}
			for (size_t sys = 0; sys < uiSystems.size(); sys++) //handles UI system updates
			{
				if (uiSystems.at(sys)->active)
				{
					uiSystems.at(sys)->Update();
					uiSystems.at(sys)->HandleEvents();
				}
			}
			performanceStats.updateTime = SDL_GetTicks() - performanceStats.updateStart;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			performanceStats.renderStart = SDL_GetTicks();
			for (size_t sys = 0; sys < systems.size(); sys++) //handles system rendering
			{
				systems.at(sys)->Render();
			}
			for (size_t sys = 0; sys < uiSystems.size(); sys++) //handles UI system rendering
			{
				if (uiSystems.at(sys)->active)
				{
					uiSystems.at(sys)->Render();
				}
			}
			performanceStats.renderTime = SDL_GetTicks() - performanceStats.renderStart;
			SDL_GL_SwapWindow(screen->GetWindow());

			performanceStats.physicsStart = SDL_GetTicks();
			ThreadingManager::JoinThread(physicsThread);
			performanceStats.physicsTime = SDL_GetTicks() - performanceStats.physicsStart;

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
			InputManager::ClearFrameInputs();

			performanceStats.UpdatePerformanceStats();
		}

		physicsWorld->CleanupPhysicsWorld();
	}

	std::shared_ptr<Scene> Application::CreateScene()
	{
		std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
		scenes.push_back(newScene);

		return newScene;
	}

	void Application::ChangeScene(int index)
	{
		activeScene = scenes.at(index);

		entities.clear();
		uiSystems.clear();
		for (int i = 0; i < systems.size(); i++)
		{
			systems.at(i)->ClearAllComponents();
		}

		entities = activeScene->sceneEntities;
		uiSystems = activeScene->sceneInterfaces;
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

	std::shared_ptr<Entity> Application::CreateEntity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		std::shared_ptr<Entity> en = std::make_shared<Entity>();
		if (availableIDs.size() > 0)
		{
			int id = availableIDs.at(0);
			std::vector<int>::iterator it = availableIDs.begin();
			availableIDs.erase(it);

			en->entityID = id;
			en->self = en;
			en->AddComponent<Transform>(position, rotation, scale);
			entities.at(id) = en;
			return en;
		}
		en->entityID = entities.size();
		en->self = en;
		en->AddComponent<Transform>(position, rotation, scale);
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
		BindSystem<LightSystem>(true, true);
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