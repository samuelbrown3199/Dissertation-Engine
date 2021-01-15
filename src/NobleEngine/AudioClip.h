#include <string>
#include <vector>

#include <AL/al.h>

#include "Resource.h"

namespace NobleEngine
{
	struct AudioClip : public Resource
	{
		ALuint audioClipID;

		void OnLoad();
		void LoadOgg(const std::string& fileDirectory, std::vector<char>& buffer, ALenum& format, ALsizei& freq);
	};
}