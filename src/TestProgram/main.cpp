#include <iostream>
#include <thread>

#include <NobleEngine/EngineCore.h>
#include <NobleEngine/TransformSystem.h>

using namespace NobleEngine;
int main()
{
	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program");

	std::shared_ptr<Entity> testEntity = app->CreateEntity();
	testEntity->AddComponent<Transform>();

	std::shared_ptr<Shader> shader = app->GetResourceManager()->LoadResource<Shader>("Resources\standard.vs");

	app->MainLoop();

	return 0;
}