#pragma once
#include <AL\alc.h>

// If its not a singleton numerous devices can be created

class SoundDevice
{
public:
	static SoundDevice* get();
private:
	SoundDevice();
	~SoundDevice();

	ALCdevice* alc_device;
	ALCcontext* alc_context;
};

