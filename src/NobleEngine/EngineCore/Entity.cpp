#include "Entity.h"

#include "Application.h"

namespace NobleEngine
{
	int Entity::GetEntityComponentSize()
	{
		return entityComponents.size();
	}

	void Entity::Destroy()
	{
		Application::deletionEntities.push_back(self.lock());
	}
}