
#include "AudioListenerSystem.h"

namespace NobleEngine
{
	SetupComponentList(AudioListener);

	void AudioListenerSystem::OnUpdate(std::shared_ptr<AudioListener> comp)
	{
		if (comp->listenerTransform)
		{
			alListener3f(AL_POSITION, comp->listenerTransform->position.x, comp->listenerTransform->position.y, comp->listenerTransform->position.z);
			alListener3f(AL_ORIENTATION, comp->listenerTransform->rotation.x, comp->listenerTransform->rotation.y, comp->listenerTransform->rotation.z);
		}
	}
}