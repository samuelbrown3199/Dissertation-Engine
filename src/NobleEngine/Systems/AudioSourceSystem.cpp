#include "AudioSourceSystem.h"

#include "../Components/Transform.h"
#include "../EngineCore/Entity.h"

namespace NobleEngine
{
	SetupComponentList(AudioSource);

	void AudioSourceSystem::OnUpdate(std::shared_ptr<AudioSource> comp)
	{
		if (!comp->checkForTransform)
		{
			comp->sourceTransform = Application::GetEntity(comp->entityID)->GetComponent<Transform>();
			comp->checkForTransform = true;
		}

		ALenum state;
		if (comp->sourceID)
		{
			alGetSourcei(comp->sourceID, AL_SOURCE_STATE, &state);
		}
		if (comp->play)
		{
			if (!comp->sourceID)
			{
				alGenSources(1, &comp->sourceID);
			}

			if (comp->sourceTransform)
			{
				alSource3f(comp->sourceID, AL_POSITION, comp->sourceTransform->position.x, comp->sourceTransform->position.y, comp->sourceTransform->position.z);
			}
			alSource3f(comp->sourceID, AL_VELOCITY, comp->velocity.x, comp->velocity.y, comp->velocity.z);

			alSourcei(comp->sourceID, AL_LOOPING, comp->loop);
			alSourcef(comp->sourceID, AL_PITCH, comp->pitch);
			alSourcef(comp->sourceID, AL_GAIN, comp->gain);

			if (state != AL_PLAYING)
			{
				alSourcei(comp->sourceID, AL_BUFFER, comp->clip->audioClipID);
				alSourcePlay(comp->sourceID);
			}
			else
			{
				if (!comp->loop)
				{
					comp->play = false;
				}
			}
		}
		else
		{
			if (state != AL_PLAYING)
			{
				alSourceStop(comp->sourceID);
				alDeleteSources(1, &comp->sourceID);
			}
		}
	}
}