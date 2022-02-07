#pragma once
#include <AL\al.h>
#include <vector>

class SampleBuffer
{
public:
	static SampleBuffer* get();

	ALuint play_sample_and_increase_history(const char* fileName);
	bool remove_a_sample_from_this_history(const ALuint& sample);

private:
	SampleBuffer();
	~SampleBuffer();

	// A vector of samples
	std::vector<ALuint> samples_vector;
};

