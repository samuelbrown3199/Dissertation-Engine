#include <iostream>
#include <thread>
#include <chrono>

#include <NobleEngine/EngineCore.h>
#include "FlyingCamSystem.h"
#include "RotatorSystem.h"
using namespace NobleEngine;
int main()
{
	srand(time(NULL));

	std::shared_ptr<Application> app = Application::InitializeEngine("Test Program", 1366, 768);

	std::string modelLoc = "Resources\\Models\\cube.obj";
	std::string texLoc = "Resources\\Textures\\test.png";
	std::string texLoc1 = "";
	std::string testSpriteSheet = "Resources\\Textures\\testspritesheet.png";
	std::string testFont = "Resources\\Fonts\\test.ttf";
	std::string testAudio = "Resources\\Sound\\testsound.ogg";

	std::shared_ptr<AudioClip> ac = app->GetResourceManager()->LoadResource<AudioClip>(testAudio);
	std::shared_ptr<Font> font = ResourceManager::LoadResource<Font>(testFont);

	int amount = 5;
	for (int x = 0; x < amount; x++)
	{
		for (int z = 0; z < amount; z++)
		{
			for (int y = 0; y < amount; y++)
			{
				std::shared_ptr<Entity> physicsTest = app->CreateEntity();
				std::shared_ptr<Transform> tr = physicsTest->AddComponent<Transform>(glm::vec3(-50 + (15 * x) + rand() % 5, 20 + (15 * y) + rand() % 5, 50 + (-15 * z) + rand() % 5), glm::vec3(rand() % 360, rand() % 360, rand() % 360));
				std::shared_ptr<MeshRenderer> pc = physicsTest->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc, texLoc1));
				physicsTest->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 20);
			}
		}
	}

	std::shared_ptr<Entity> floorEntity = app->CreateEntity();
	std::shared_ptr<Transform> tr = floorEntity->AddComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1000, 1, 1000));
	floorEntity->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 0);
	std::shared_ptr<MeshRenderer> mr = floorEntity->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc, texLoc1));

	std::shared_ptr<Entity> testPointLight = app->CreateEntity();
	testPointLight->AddComponent<Transform>(glm::vec3(0, 5, 0), glm::vec3(0, -90, 0));
	testPointLight->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc, texLoc1));
	testPointLight->AddComponent<Light>();
	testPointLight->AddComponent<Rotator>();

	//TRANSFORM PARENT TESTING
	/*std::shared_ptr<Entity> physicsTest = app->CreateEntity();
	tr = physicsTest->AddComponent<Transform>(glm::vec3(0, 50, -30), glm::vec3(rand() % 360, rand() % 360, rand() % 360));
	std::shared_ptr<MeshRenderer> pc = physicsTest->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc, texLoc1));
	physicsTest->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 20);

	std::shared_ptr<Entity> parentTest = Application::CreateEntity();
	std::shared_ptr<Transform> tr2 = parentTest->AddComponent<Transform>(glm::vec3(1, 1, 1));
	tr2->parent = tr;
	pc = parentTest->AddComponent<MeshRenderer>(modelLoc, app->GetResourceManager()->LoadMaterial(texLoc, texLoc1));*/

	std::shared_ptr<Entity> camera = app->CreateEntity();
	camera->AddComponent<Transform>(glm::vec3(0, 5, 0));
	std::shared_ptr<Camera> cr = camera->AddComponent<Camera>();
	camera->AddComponent<FlyingCam>();

	app->BindSystem<FlyingCamSystem>(true, false);
	app->BindSystem<RotatorSystem>(true, false);
	app->activeCam = cr;

	app->MainLoop();

	return 0;
}