#include "ALAddressBlock.h"
#include <AL\alc.h>
#include <stdio.h>

ALAddressBlock* ALAddressBlock::get()
{
	static ALAddressBlock* sound_device = new ALAddressBlock();
	return sound_device;
}

ALAddressBlock::ALAddressBlock()
{
	this->alc_device = alcOpenDevice(nullptr); // Default device
	if (this->alc_device)
	{
		this->alc_context = alcCreateContext(this->alc_device, nullptr);

		/* If context fails */
		if (!this->alc_context)
		{
			throw("AL device could not assign its context.\n");
		}

		if (!alcMakeContextCurrent(this->alc_context))
		{
			throw("Context is not assignable to the AL process\n");
		}
		else {
			const ALCchar* name = NULL;

			if (alcIsExtensionPresent(this->alc_device, "ALC_ENUMERATE_ALL_EXT"))
			{
				name = alcGetString(this->alc_device, ALC_ALL_DEVICES_SPECIFIER);
				if (!name || alcGetError(this->alc_device) != ALC_NO_ERROR)
				{
					name = alcGetString(this->alc_device, ALC_DEVICE_SPECIFIER);
				}
			}
			printf("Opened \%s\n", name);
		}
	}
	else {
		throw("AL device is not valid.");
	}
}

ALAddressBlock::~ALAddressBlock()
{
	if (!alcMakeContextCurrent(nullptr))
	{
		throw("Failed to make context current using a null pointer.\n");
	}

	alcDestroyContext(this->alc_context);
	if (this->alc_context)
	{
		throw("The context could not be deallocated.\n");
	}

	if (!alcCloseDevice(this->alc_device))
	{
		throw("The AL device could not be closed.\n");
	}
}