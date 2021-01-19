
#include "../EngineCore/System.h"
#include "../Components/AudioSource.h"

namespace NobleEngine
{
	/**
	*Handles the functionality of audio sources. Automatically bound to the engine on startup.
	*/
	struct AudioSourceSystem : public System<AudioSource>
	{
		void OnUpdate(std::shared_ptr<AudioSource> comp);
	};
}