#include <iostream>
#include <thread>

#include <NobleEngine/EngineCore.h>
#include <NobleEngine/TransformSystem.h>
#include <NobleEngine/MeshRendererSystem.h>
#include <NobleEngine/Model.h>

using namespace NobleEngine;
int main()
{
	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program");

	std::shared_ptr<Entity> testEntity = app->CreateEntity();
	testEntity->AddComponent<Transform>();
	testEntity->AddComponent<MeshRenderer>()->model = app->GetResourceManager()->LoadResource<Model>("Resources\\Models\\cube.obj");

	app->MainLoop();

	return 0;
}