#include "ALAddressBlock.h"
#include "SampleCache.h"
#include <stdio.h>
#include "PlaybackBuffer.h"
#include <windows.h>

#include "use_dsp_utils_namespace.h"

FunctionGenerator functionGenerator;

void check_for_an_error(ALenum error);

void play_from_dsp_util_test_file()
{
	uint32_t testing_vectors = SampleCache::get()->add_to_vector("C:\\development\\open_al-gl_digital_audio_workstation\\dsp_utils\\sine.wav");
	PlaybackBuffer main_buffer;
	main_buffer.play(testing_vectors);
}

void play_from_pcm_raw_data()
{
	ALenum al_comparator = alGetError();

	unsigned int buffer_feed = 0;
	alGenBuffers(1, &buffer_feed);
	check_for_an_error(al_comparator);

	int sampleRate = 44100;
	int bitDepth = 16;
	int numberOfChannels = 2;
	int amplitudeLimiter = (pow(2, (bitDepth - 1))) - 1;
	int seconds = 16;
	unsigned long long buffer_feed_duration = sampleRate * seconds;

	// The al buffer seems to always divide by two unless set. Not currently in the mood to investigate that.
	unsigned long long al_channel_inversion_multiplier = buffer_feed_duration * 2;

	double frequency = 256.0f;
	short* sineWave = new short[buffer_feed_duration];

	for (int i = 0; i < buffer_feed_duration; i++)
	{
		sineWave[i] = functionGenerator.get_sine(i, frequency, sampleRate) * (amplitudeLimiter / 4);
	}
	alBufferData(buffer_feed, AL_FORMAT_STEREO16, sineWave, al_channel_inversion_multiplier, sampleRate / numberOfChannels);
	check_for_an_error(al_comparator);

	ALuint alpha_buffer = 0;
	alGenSources(1, &alpha_buffer);
	// Add the optimal buffer to the al source (buffer)
	alSourcei(alpha_buffer, AL_BUFFER, buffer_feed);
	alSourcePlay(alpha_buffer);

	Sleep(seconds * 1000);
	printf("Completed without exiting.\n");
}

int main()
{
	ALAddressBlock* global_AL_address = ALAddressBlock::get();

	/*
	Reading from a file:
	*/

	// play_from_dsp_util_test_file();

	/*
	Playing raw pcm data:
	*/

	play_from_pcm_raw_data();

	return 0;
}

void check_for_an_error(ALenum error)
{
	error = alGetError();
	if (error)
	{
		printf("AL error occurred: %i", error);
	}
}