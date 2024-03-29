#include <NobleEngine/EngineCore/Entity.h>

#include "DeleterSystem.h"

SetupComponentList(Deleter);

void DeleterSystem::OnUpdate(std::shared_ptr<Deleter> comp)
{
	comp->framesSinceCreation++;
	if (comp->framesSinceCreation >= comp->framesToDelete)
	{
		comp->GetEntity()->Destroy();
	}
}