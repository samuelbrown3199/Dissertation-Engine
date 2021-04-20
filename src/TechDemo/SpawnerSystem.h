#include <NobleEngine/EngineCore/System.h>

#include"Spawner.h"

using namespace NobleEngine;
struct SpawnerSystem : public System<Spawner>
{
	void OnUpdate(std::shared_ptr<Spawner> comp);
};