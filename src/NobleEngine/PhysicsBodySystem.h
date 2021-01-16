#include "System.h"
#include "PhysicsBody.h"

namespace NobleEngine
{
	/**
	*Responsible for updating physics body objects.
	*/
	struct PhysicsBodySystem : public System<PhysicsBody>
	{
		void OnUpdate(std::shared_ptr<PhysicsBody> comp);
	};
}