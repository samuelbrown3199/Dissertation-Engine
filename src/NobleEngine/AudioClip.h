#include <string>
#include <vector>

#include <AL/al.h>

#include "Resource.h"

namespace NobleEngine
{
	class AudioClip : public Resource
	{
		ALuint audioClipID;

		void OnLoad();
		void LoadOgg(std::string& fileDirectory, std::vector<char>& buffer, ALenum& format, ALsizei& freq);
	};
}