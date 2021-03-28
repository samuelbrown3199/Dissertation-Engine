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
		void LoadOgg(const std::string& _fileDirectory, std::vector<char>& _buffer, ALenum& _format, ALsizei& _freq);
	};
}

#endif