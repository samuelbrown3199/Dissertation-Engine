#include "Application.h"

#include "System.h"
#include "Entity.h"
#include "TransformSystem.h"

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
		BindCoreSystems();

		SDL_Event e = { 0 };
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		
		glClearColor(0.0f, 0.45f, 0.45f, 1.0f);

		while (loop)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					loop = false;
				}
			}
			for (size_t sys = 0; sys < systems.size(); sys++) //handles system updates
			{
				systems.at(sys)->Update();
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//render here

			SDL_GL_SwapWindow(window);

			for (size_t en = 0; en < entities.size(); en++)
			{
				std::shared_ptr<Entity> entity = entities.at(en);
				if (entity->GetDeletion())
				{
					RemoveEntity(entity->entityID);
				}
			}
		}
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
			entities.at(id) = en;
		}
		en->entityID = entities.size();
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
			entities.at(id) = en;
		}
		en->entityID = entities.size();
		en->tag = tag;
		entities.push_back(en);

		return en;
	}

	std::shared_ptr<Entity> Application::GetEntity(int ID)
	{
		for (size_t en = 0; en < entities.size(); en++)
		{
			if (entities.at(en)->entityID == ID)
			{
				return entities.at(en);
			}
		}

		std::cout << "Entity could not be found with ID: " << ID << std::endl;
		throw std::exception();
	}

	void Application::BindCoreSystems()
	{
		std::shared_ptr<TransformSystem> tr = std::make_shared<TransformSystem>();
		BindSystem(tr);
	}

	void Application::RemoveEntity(int ID)
	{
		entities.erase(entities.begin() + ID);
	}
}