#include <iostream>
#include <NobleEngine/EngineCore.h>

using namespace NobleEngine;
int main()
{
	std::cout << "Hello World!" << std::endl;
	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program");

	std::shared_ptr<TransformSystem> tr = std::make_shared<TransformSystem>();
	app->BindSystem(tr);

	app->MainLoop();
	
	return 0;
}