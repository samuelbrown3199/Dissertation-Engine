#include <iostream>
#include <thread>
#include <chrono>

#include <NobleEngine/EngineCore.h>
#include <NobleEngine/TransformSystem.h>
#include <NobleEngine/MeshRendererSystem.h>
#include <NobleEngine/CameraSystem.h>
#include <NobleEngine/AudioClip.h>

#include "FlyingCamSystem.h"

using namespace NobleEngine;
int main()
{
	srand(time(NULL));

	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program", 900, 900);

	std::string modelLoc = "Resources\\Models\\cube.obj";
	std::string texLoc = "Resources\\Textures\\test.png";
	std::string texLoc1 = "";
	std::string testAudio = "Resources\\Sound\\testsound.ogg";

	std::shared_ptr<AudioClip> ac = app->GetResourceManager()->LoadResource<AudioClip>(testAudio);

	int amount = 10;
	for (int x = 0; x < amount; x++)
	{
		for (int z = 0; z < amount; z++)
		{
			for (int y = 0; y < amount; y++)
			{
				std::shared_ptr<Entity> physicsTest = app->CreateEntity();
				std::shared_ptr<Transform> tr = physicsTest->AddComponent<Transform>();

				tr->position = glm::vec3(25 + (-5 * x) + rand() % 5, 50 + (5 * y) + rand() % 5, -30 + (-5 * z) + rand() % 5);
				tr->rotation = glm::vec3(rand() % 360, rand() % 360, rand() % 360);
				std::shared_ptr<MeshRenderer> pc = physicsTest->AddComponent<MeshRenderer>();
				pc->model = app->GetResourceManager()->LoadResource<NobleEngine::Model>(modelLoc);
				pc->material = app->GetResourceManager()->LoadMaterial(texLoc, texLoc1);
				/*physicsTest->AddComponent<Collider>(Collider::ColliderShape::box);
				physicsTest->AddComponent<PhysicsBody>(20);*/
			}
		}
	}

	std::shared_ptr<Entity> testEntity = app->CreateEntity();
	std::shared_ptr<Transform> tr = testEntity->AddComponent<Transform>();
	tr->position = glm::vec3(0, 0, 0);
	tr->scale = glm::vec3(100, 1, 100);

	std::shared_ptr<MeshRenderer> mr = testEntity->AddComponent<MeshRenderer>();
	mr->model = app->GetResourceManager()->LoadResource<NobleEngine::Model>(modelLoc);
	mr->material = app->GetResourceManager()->LoadMaterial(texLoc, texLoc1);

	std::shared_ptr<Entity> camera = app->CreateEntity();
	camera->AddComponent<Transform>()->position;
	std::shared_ptr<Camera> cr = camera->AddComponent<Camera>();
	camera->AddComponent<FlyingCam>();

	std::shared_ptr<FlyingCamSystem> fc = std::make_shared<FlyingCamSystem>();
	fc->SetSystemUse(false, true, false);
	app->BindSystem(fc);

	app->activeCam = cr;

	app->MainLoop();

	return 0;
}