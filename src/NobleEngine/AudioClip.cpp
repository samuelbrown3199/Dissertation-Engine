#include "AudioClip.h"

#include "stb_vorbis.h"

namespace NobleEngine
{
	void AudioClip::OnLoad()
	{
		alGenBuffers(1, &audioClipID);
		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<char> bufferData;
		LoadOgg(resourcePath, bufferData, format, freq);

		alBufferData(audioClipID, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
	}

	void AudioClip::LoadOgg(std::string& fileDirectory, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename(fileDirectory.c_str(), &channels, &sampleRate, &output);
		if (samples == -1)
		{
			throw std::exception();
		}
		if (channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}
		freq = sampleRate;
		buffer.resize(samples * 2);
		memcpy(&buffer.at(0), output, buffer.size());

		free(output);
	}
}