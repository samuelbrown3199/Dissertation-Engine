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

	Application::activeScene->sceneEnvironment->directionalLight->direction = glm::vec3(0, -260, 0);

	int amount = 22;
	for (int x = 0; x < amount; x++)
	{
		for (int z = 0; z < amount; z++)
		{
			for (int y = 0; y < amount; y++)
			{
				std::shared_ptr<Entity> physicsTest = app->CreateEntity(glm::vec3(25 + (-15 * x) + rand() % 5, 50 + (15 * y) + rand() % 5, -30 + (-15 * z) + rand() % 5), glm::vec3(rand() % 360, rand() % 360, rand() % 360), glm::vec3(1,1,1));
				std::shared_ptr<MeshRenderer> pc = physicsTest->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc));
				//physicsTest->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 20);
			}
		}
	}

	std::shared_ptr<Entity> floorEntity = app->CreateEntity();
	std::shared_ptr<Transform> tr = floorEntity->AddComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(500, 1, 500));
	floorEntity->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 0);
	std::shared_ptr<MeshRenderer> mr = floorEntity->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc));

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