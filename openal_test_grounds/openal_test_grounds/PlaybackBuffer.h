#pragma once
#include <AL\al.h>
class PlaybackBuffer
{
public:
	PlaybackBuffer();
	~PlaybackBuffer();

	void play(const ALuint playbackBuffer);

private:
	ALuint source;
	float pitch = 1.f;
	float gain = 1.f;
	float positions[3] = { 0,0,0 };
	float velocities[3] = { 0,0,0 };
	bool shouldLoop = false;
	ALuint buffer = 0;
};

