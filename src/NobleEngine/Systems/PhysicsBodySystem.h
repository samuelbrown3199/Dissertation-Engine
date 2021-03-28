#include "../EngineCore/System.h"
#include "../Components/PhysicsBody.h"

namespace NobleEngine
{
	/**
	*Responsible for updating physics body objects. Automatically bound to the engine on startup.
	*/
	struct PhysicsBodySystem : public System<PhysicsBody>
	{
		void OnUpdate(std::shared_ptr<PhysicsBody> _comp);
	};
}