#pragma once
#ifndef AUDIOCLIP_H_
#define AUDIOCLIP_H_

#include <string>
#include <vector>

#include <AL/al.h>

#include "../EngineCore/Resource.h"

namespace NobleEngine
{
	/**
	*Stores an audio file for use in OpenAL.
	*/
	struct AudioClip : public Resource
	{
		ALuint audioClipID;
		/**
		*Loads a sound file and buffers it.
		*/
		void OnLoad();
		/**
		*Loads an OGG file.
		*/
		void LoadOgg(const std::string& fileDirectory, std::vector<char>& buffer, ALenum& format, ALsizei& freq);
	};
}

#endif