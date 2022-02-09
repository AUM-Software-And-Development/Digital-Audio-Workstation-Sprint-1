#pragma once
#include <AL\alc.h>

// If its not a singleton numerous devices can be created

class ALAddressBlock {
public:
	static ALAddressBlock* get();

private:
	ALAddressBlock();
	~ALAddressBlock();

	ALCdevice* alc_device;
	ALCcontext* alc_context;
};

