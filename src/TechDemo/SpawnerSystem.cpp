#include <NobleEngine/Components/MeshRenderer.h>
#include <NobleEngine/Components/PhysicsBody.h>

#include "SpawnerSystem.h"

SetupComponentList(Spawner);

void SpawnerSystem::OnUpdate(std::shared_ptr<Spawner> comp)
{
	comp->currentFramesSinceLastSpawn++;
	if (comp->currentFramesSinceLastSpawn >= comp->framesToSpawn)
	{
		std::shared_ptr<Entity> coin = Application::CreateEntity(glm::vec3(comp->spawnerTransform->position.x + rand() % 100, comp->spawnerTransform->position.y, comp->spawnerTransform->position.x + rand() % 100), glm::vec3(rand()%360, rand() % 360, rand() % 360), glm::vec3(1, 1, 1));
		coin->AddComponent<MeshRenderer>("Resources\\Models\\coin.obj", Application::GetResourceManager()->LoadMaterial("Resources\\Textures\\coin.png"));
		coin->AddComponent<PhysicsBody>(PhysicsBody::ColliderShape::cylinder, 1, glm::vec3(1, 0.1, 1));

		comp->currentFramesSinceLastSpawn = 0;
	}
}