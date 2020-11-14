#include <iostream>
#include <thread>

#include <NobleEngine/EngineCore.h>
#include <NobleEngine/Transform.h>

using namespace NobleEngine;
int main()
{
	std::cout << "Hello World!" << std::endl;
	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program");

	std::shared_ptr<Entity> testEntity = app->CreateEntity();
	testEntity->AddComponent(transformComponents);

	app->MainLoop();
	
	return 0;
}