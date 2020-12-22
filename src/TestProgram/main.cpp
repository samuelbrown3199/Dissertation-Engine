#include <iostream>
#include <thread>

#include <NobleEngine/EngineCore.h>
#include <NobleEngine/TransformSystem.h>
#include <NobleEngine/MeshRendererSystem.h>
#include <NobleEngine/CameraSystem.h>

#include "FlyingCamSystem.h"

using namespace NobleEngine;
int main()
{
	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program", 900, 900);

	std::string modelLoc = "Resources\\Models\\cube.obj";
	std::string texLoc = "Resources\\Textures\\test.png";
	std::string texLoc1 = "";

	std::shared_ptr<Entity> testEntity = app->CreateEntity();
	std::shared_ptr<Transform> tr = testEntity->AddComponent<Transform>();
	tr->position = glm::vec3(0, 0, -10);

	std::shared_ptr<MeshRenderer> mr = testEntity->AddComponent<MeshRenderer>();
	mr->model = app->GetResourceManager()->LoadResource<NobleEngine::Model>(modelLoc);
	mr->material = app->GetResourceManager()->LoadMaterial(texLoc, texLoc1);

	std::shared_ptr<Entity> camera = app->CreateEntity();
	camera->AddComponent<Transform>()->position;
	std::shared_ptr<Camera> cr = camera->AddComponent<Camera>();
	camera->AddComponent<FlyingCam>();

	std::shared_ptr<FlyingCamSystem> fc = std::make_shared<FlyingCamSystem>();
	app->BindSystem(fc);

	app->activeCam = cr;

	app->MainLoop();

	return 0;
}