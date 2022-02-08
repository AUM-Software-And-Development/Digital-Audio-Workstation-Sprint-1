#include "ALAddressBlock.h"
#include "SampleCache.h"
#include <stdio.h>
#include "PlaybackBuffer.h"

int main()
{
	ALAddressBlock* global_AL_address = ALAddressBlock::get();

	uint32_t testing_vectors = SampleCache::get()->add_to_vector("C:\\development\\open_al-gl_digital_audio_workstation\\dsp_utils\\sine.wav");

	PlaybackBuffer main_buffer;

	main_buffer.play(testing_vectors);

	printf("Completed without exiting.\n");

	return 0;
}