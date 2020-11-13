#include <iostream>
#include <NobleEngine/EngineCore.h>

using namespace NobleEngine;
int main()
{
	std::cout << "Hello World!" << std::endl;
	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program");
	app->MainLoop();

	return 0;
}