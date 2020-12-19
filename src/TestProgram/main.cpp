#include <iostream>
#include <thread>

#include <NobleEngine/EngineCore.h>
#include <NobleEngine/TransformSystem.h>
#include <NobleEngine/MeshRendererSystem.h>
#include <NobleEngine/CameraSystem.h>

using namespace NobleEngine;
int main()
{
	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program", 900, 900);

	std::shared_ptr<Entity> testEntity = app->CreateEntity();
	std::shared_ptr<Transform> tr = testEntity->AddComponent<Transform>();
	tr->position = glm::vec3(0, 0, -10);

	std::shared_ptr<MeshRenderer> mr = testEntity->AddComponent<MeshRenderer>();
	mr->model = app->GetResourceManager()->LoadResource<NobleEngine::Model>("Resources\\Models\\cube.obj");

	std::shared_ptr<Entity> camera = app->CreateEntity();
	camera->AddComponent<Transform>()->position;
	std::shared_ptr<Camera> cr = camera->AddComponent<Camera>();
	app->activeCam = cr;

	app->MainLoop();

	return 0;
}