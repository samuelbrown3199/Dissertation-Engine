#include "AudioClip.h"

#include <iostream>

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

    void AudioClip::LoadOgg(const std::string& fileDirectory, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
    {
        int channels = 0;
        int sampleRate = 0;
        short* output = NULL;
        int samples = stb_vorbis_decode_filename(fileDirectory.c_str(), &channels, &sampleRate, &output);
        int amountOfBytesPerSample = 0;
        if (samples == -1)
        {
            std::cout << "Failed to open file " << fileDirectory << std::endl;
            throw std::exception();
        }
        // Record the format required by OpenAL
        if (channels == 1)
        {
            format = AL_FORMAT_MONO16;
            amountOfBytesPerSample = 2;
        }
        else
        {
            format = AL_FORMAT_STEREO16;
            amountOfBytesPerSample = 4;
        }
        // Record the sample rate required by OpenAL
        freq = sampleRate;
        buffer.resize(samples * amountOfBytesPerSample);
        memcpy(&buffer.at(0), output, buffer.size());
        // Clean up the read data
        free(output);
    }
}