
#include "../EngineCore/System.h"
#include "../Components/AudioListener.h"

namespace NobleEngine
{
	/**
	*Handles and updates audio listeners. Automatically bound to the engine on startup.
	*/
	struct AudioListenerSystem : public System<AudioListener>
	{
		void OnUpdate(std::shared_ptr<AudioListener> _comp);
	};
}