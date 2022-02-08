#include "PlaybackBuffer.h"
#include <stdio.h>

PlaybackBuffer::PlaybackBuffer()
{
	/* This seems like an invasive shortcut, but this section just applies amplitudes to the source sample.
	* the buffer can be written manually when needed...
	*/

	// Params: position handles channel phase. Does not seem to relate to array phase
	alGenSources(1, &this->source);
	alSourcef(this->source, AL_PITCH, this->pitch);
	alSourcef(this->source, AL_GAIN, this->gain);
	alSource3f(this->source, AL_POSITION, this->positions[0], this->positions[1], this->positions[2]);
	alSource3f(this->source, AL_VELOCITY, this->velocities[0], this->velocities[1], this->velocities[2]);
	alSourcei(this->source, AL_LOOPING, this->shouldLoop);
	alSourcei(this->source, AL_BUFFER, this->buffer);
}

PlaybackBuffer::~PlaybackBuffer()
{
	alDeleteSources(1, &this->source);
}

void PlaybackBuffer::play(const ALuint playbackBuffer)
{
	if (playbackBuffer != this->buffer)
	{
		this->buffer = playbackBuffer;
		// Set the buffer to relevant
		alSourcei(this->source, AL_BUFFER, (ALint)this->buffer);
	}

	alSourcePlay(this->source);

	ALint status = AL_PLAYING;
	printf("Sample is outputting.");

	while (status == AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		printf("Sample processing.");
		alGetSourcei(this->source, AL_SOURCE_STATE, &status);
	}
	printf("Sample is no longer processing.");
}
