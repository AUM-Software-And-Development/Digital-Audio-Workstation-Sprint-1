#include "SampleCache.h"
#include <sndfile.h>
#include <inttypes.h>
#include <AL\alext.h>

SampleCache* SampleCache::get()
{
	static SampleCache* sampleBuffer = new SampleCache();
	return sampleBuffer;
}

/* Make this a buffer middle man - Takes file, or array, with a switch arg */
ALuint SampleCache::add_to_vector(const char* fileName)
{
	SNDFILE* sampleFile;
	
	/* This class uses the word frames instead of samples
	   it seems to be a gaming industry name rather than an audio industry name
	   to create a "raw" wave array for the buffer, simply generate an array of samples.
	*/
	SF_INFO sfInfo;

	// Open file and validate
	sampleFile = sf_open(fileName, SFM_READ, &sfInfo);

	if (!sampleFile)
	{
		fprintf(stderr, "The sample was not valid for %s, error: %s\n", fileName, sf_strerror(sampleFile));
		return 0;
	}

	if (sfInfo.frames < 1 || sfInfo.frames >(sf_count_t) (INT_MAX / sizeof(short)) / sfInfo.channels)
	{
		fprintf(stderr, "Sample from %s does not align.\n", fileName);
		sf_close(sampleFile);
		return 0;
	}

	ALenum format;
	format = AL_NONE;
	
	if (sfInfo.channels == 1)
	{
		format = AL_FORMAT_MONO16;
	}
	else if (sfInfo.channels == 2)
	{
		format = AL_FORMAT_STEREO16;
	}

	if (!format)
	{
		fprintf(stderr, "Channel count too high. Are you crazy?? This many: %d\n", sfInfo.channels);
		sf_close(sampleFile);
	}

	/**/
	/* "Raw" wave data */
	/**/

	short* localBuffer;
	localBuffer = static_cast<short*>(malloc((size_t)(sfInfo.frames * sfInfo.channels) * sizeof(short)));

	sf_count_t numberOfFrames;
	numberOfFrames = sf_readf_short(sampleFile, localBuffer, sfInfo.frames);
	if (numberOfFrames < 1)
	{
		free(localBuffer);
		sf_close(sampleFile);
		fprintf(stderr, "Did not read any samples from %s.\n", fileName);
		return 0;
	}

	ALsizei numberOfBytes;
	numberOfBytes = (ALsizei)(numberOfFrames * sfInfo.channels) * (ALsizei)sizeof(short);

	ALuint playbackBuffer;
	/* Takes arg of bytes at buffer address, channel count argument, buffer, num bytes aka size, SR/Second */
	alGenBuffers(1, &playbackBuffer);
	alBufferData(playbackBuffer, format, localBuffer, numberOfBytes, sfInfo.samplerate);

	// Done adding to buffer
	free(localBuffer);
	sf_close(sampleFile);

	ALenum error_check = alGetError();

	if (error_check)
	{
		fprintf(stderr, "OpenAL errored out due to this: %s\n", alGetString(error_check));
		if (playbackBuffer && alIsBuffer(playbackBuffer))
		{
			alDeleteBuffers(1, &playbackBuffer);
		}
	}

	this->samples_vector.push_back(playbackBuffer);

	return playbackBuffer;
}

bool SampleCache::remove_from_vector(const ALuint& sample)
{
	auto samples = this->samples_vector.begin();
	while (samples != this->samples_vector.end())
	{
		if (*samples == sample)
		{
			alDeleteBuffers(1, &*samples);
			samples = this->samples_vector.erase(samples);
			return true;
		}
		else {
			++samples;
		}
	}


	return false;
}

SampleCache::SampleCache()
{
	this->samples_vector.clear();
}

SampleCache::~SampleCache()
{
	alDeleteBuffers(this->samples_vector.size(), this->samples_vector.data());
	this->samples_vector.clear();
}