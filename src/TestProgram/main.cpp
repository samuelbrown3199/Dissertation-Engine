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

	std::shared_ptr<TransformSystem> tr = std::make_shared<TransformSystem>();
	app->BindSystem(tr);

	app->MainLoop();
	
	return 0;
}

//std::vector<std::shared_ptr<Transform>> Transform::transformComponents;
//REGISTER(Transform)