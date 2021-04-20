#include <NobleEngine/EngineCore/Entity.h>
#include <NobleEngine/EngineCore/Component.h>
#include <NobleEngine/Components/Transform.h>

using namespace NobleEngine;
struct Spawner : public Component<Spawner>
{
	std::shared_ptr<Transform> spawnerTransform;

	float framesToSpawn = 3;
	float currentFramesSinceLastSpawn = 0;

	void OnInitialize()
	{
		spawnerTransform = GetEntity()->GetComponent<Transform>();
	}
};