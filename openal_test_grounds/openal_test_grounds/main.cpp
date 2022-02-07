#include "SoundDevice.h"
#include "SampleBuffer.h"
#include <stdio.h>

int main()
{
	SoundDevice* testing_bufferability = SoundDevice::get();
	uint32_t testing_vectors = SampleBuffer::get()->play_sample_and_increase_history("C:/development/open_al-gl_digital_audio_workstation/openal_test_grounds/openal_test_grounds/snare_drum.wav");

	printf("No errors.\n");

	return 0;
}