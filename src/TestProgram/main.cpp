#include <iostream>
#include <thread>
#include <chrono>

#include <NobleEngine/EngineCore.h>
#include "FlyingCamSystem.h"
#include "RotatorSystem.h"
#include "TestUI.h"
using namespace NobleEngine;
int main()
{
	srand(time(NULL));

	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program", 1366, 768);

	std::string modelLoc = "Resources\\Models\\cube.obj";
	std::string modelLoc2 = "Resources\\Models\\buildings\\Residential Buildings 001.obj";
	std::string texLoc = "Resources\\Textures\\test.png";
	std::string texLoc1 = "Resources\\Models\\buildings\\textures\\AussenWand_C.jpg";
	std::string testSpriteSheet = "Resources\\Textures\\testspritesheet.png";
	std::string testFont = "Resources\\Fonts\\test.ttf";
	std::string testAudio = "Resources\\Sound\\testsound.ogg";

	std::shared_ptr<AudioClip> ac = app->GetResourceManager()->LoadResource<AudioClip>(testAudio);

	Application::activeScene->sceneEnvironment->directionalLight->direction = glm::vec3(0, 260, 0);

	int amount = 5;
	for (int x = 0; x < amount; x++)
	{
		for (int z = 0; z < amount; z++)
		{
			for (int y = 0; y < amount; y++)
			{
				std::shared_ptr<Entity> physicsTest = app->CreateEntity();
				std::shared_ptr<Transform> tr = physicsTest->AddComponent<Transform>(glm::vec3(-50 + (15 * x) + rand() % 5, 20 + (15 * y) + rand() % 5, 50 + (-15 * z) + rand() % 5), glm::vec3(rand() % 360, rand() % 360, rand() % 360));
				std::shared_ptr<MeshRenderer> pc = physicsTest->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc));
				physicsTest->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 20);
			}
		}
	}

	std::shared_ptr<Entity> light = app->CreateEntity();
	light->AddComponent<Transform>(glm::vec3(0, 5, 0));
	light->AddComponent<Light>();

	std::shared_ptr<Entity> floorEntity = app->CreateEntity();
	std::shared_ptr<Transform> tr = floorEntity->AddComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1000, 1, 1000));
	floorEntity->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 0);
	std::shared_ptr<MeshRenderer> mr = floorEntity->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc));
	
	/*
	std::shared_ptr<Entity> tankEntity = app->CreateEntity();
	tr = tankEntity->AddComponent<Transform>(glm::vec3(75, 2, 0), glm::vec3(0, -30, 0), glm::vec3(10, 10, 10));
	mr = tankEntity->AddComponent<MeshRenderer>(modelLoc2, app->GetResourceManager()->LoadMaterial(texLoc1));
	mr->material->shininess = 0.1;
	*/

	std::shared_ptr<Entity> test2D = app->CreateEntity();
	test2D->AddComponent<Transform>(glm::vec3(0, 15, 0));
	test2D->AddComponent<SpriteRenderer>(testSpriteSheet);

	std::shared_ptr<Entity> camera = app->CreateEntity();
	camera->AddComponent<Transform>(glm::vec3(0, 5, 0));
	std::shared_ptr<Camera> cr = camera->AddComponent<Camera>(true);
	camera->AddComponent<FlyingCam>();

	app->BindSystem<FlyingCamSystem>(true, false);
	app->BindSystem<RotatorSystem>(true, false);

	app->BindUISystem<TestUI>();

	app->MainLoop();

	return 0;
}