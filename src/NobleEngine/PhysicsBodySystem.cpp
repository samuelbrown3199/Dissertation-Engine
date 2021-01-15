#include "PhysicsBodySystem.h"

namespace NobleEngine
{
	SetupComponentList(PhysicsBody);

	void PhysicsBodySystem::OnUpdate(std::shared_ptr<PhysicsBody> comp)
	{
		if (comp->rigidBody && comp->rigidBody->getMotionState())
		{
			comp->rigidBody->getMotionState()->getWorldTransform(comp->bodyTransform);
		}
	}
}