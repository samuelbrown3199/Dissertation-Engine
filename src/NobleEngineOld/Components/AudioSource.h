#pragma once
#ifndef AUDIOSOURCE_H_
#define AUDIOSOURCE_H_

#include "../EngineCore/Component.h"
#include "../ResourceManagement/AudioClip.h"
#include "Transform.h"
#include "../EngineCore/ResourceManager.h"

#include <AL/al.h>

namespace NobleEngine
{
	/**
	*Stores information on an audio source.
	*/
	struct AudioSource : public Component<AudioSource>
	{
		bool checkForTransform = false;

		AudioSource()
		{
			alGenSources(1, &sourceID);
		}
		~AudioSource()
		{
			alDeleteSources(1, &sourceID);
		}

		ALuint sourceID;
		/**
		*The transform component from the entity.
		*/
		std::shared_ptr<Transform> sourceTransform;
		/**
		*The audio sources current audio clip.
		*/
		std::shared_ptr<AudioClip> clip;
		/**
		*Determines whether the audio source will loop.
		*/
		bool loop = false;
		/**
		*Determines the audio pitch.
		*/
		float pitch = 1;
		/**
		*Determines the audio volume.
		*/
		float gain = 1;
		/**
		*Stores the velocity of the audio source.
		*/
		glm::vec3 velocity = glm::vec3(0, 0, 0);
		/**
		*Determines whether the audio sources should play.
		*/
		bool play = false;
		/**
		*Initializes an audio source. Creates it with an audio clip.
		*/
		void OnInitialize(std::string audioClipLocation)
		{
			clip = ResourceManager::LoadResource<AudioClip>(audioClipLocation);
		}
		/**
		*Initializes an audio source. Creates it with an audio clip and whether you want it to play.
		*/
		void OnInitialize(std::string audioClipLocation, bool playOnStart)
		{
			clip = ResourceManager::LoadResource<AudioClip>(audioClipLocation);
			play = playOnStart;
		}
		/**
		*Initializes an audio source. Creates it with an audio clip, whether you want it to play, volume, pitch and loop.
		*/
		void OnInitialize(std::string audioClipLocation, bool playOnStart, float volume, float pitchValue, bool looping)
		{
			clip = ResourceManager::LoadResource<AudioClip>(audioClipLocation);
			play = playOnStart;
			gain = volume;
			pitch = pitchValue;
			loop = looping;
		}
	};
}

#endif