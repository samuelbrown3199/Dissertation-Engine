#include <NobleEngine/EngineCore.h>

#include "TechDemoUI.h"
#include "FlyingCamSystem.h"
#include "SpawnerSystem.h"
#include "DeleterSystem.h"

using namespace NobleEngine;
int main()
{
	srand(time(NULL));

	std::shared_ptr<Application> app = Application::InitializeEngine("Tech Demo", 1366, 768);
	Application::activeScene->sceneEnvironment->directionalLight->direction = glm::vec3(0, -260, 0);

	std::shared_ptr<Entity> floorEntity = app->CreateEntity();
	std::shared_ptr<Transform> tr = floorEntity->AddComponent<Transform>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(500, 1, 500));
	floorEntity->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::box, 0);
	std::shared_ptr<MeshRenderer> mr = floorEntity->AddComponent<MeshRenderer>("Resources\\Models\\cube.obj", app->GetResourceManager()->LoadMaterial("Resources\\Textures\\test.png"));

	std::shared_ptr<Entity> spawner = app->CreateEntity(glm::vec3(0, 300, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	spawner->AddComponent<Spawner>();

	std::shared_ptr<Entity> camera = app->CreateEntity();
	camera->AddComponent<Transform>(glm::vec3(0, 5, 0));
	camera->AddComponent<FlyingCam>();
	camera->AddComponent<AudioListener>();
	std::shared_ptr<Camera> cr = camera->AddComponent<Camera>(true);

	app->BindSystem<FlyingCamSystem>(true, false);
	app->BindSystem<SpawnerSystem>(true, false);
	app->BindSystem<DeleterSystem>(true, false);

	app->MainLoop();
	return 0;
}