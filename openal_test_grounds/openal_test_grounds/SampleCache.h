#pragma once
#include <AL\al.h>
#include <vector>

class SampleCache {
public:
	static SampleCache* get();

	ALuint add_to_vector(const char* fileName);
	bool remove_from_vector(const ALuint& sample);

private:
	SampleCache();
	~SampleCache();

	// A vector of samples
	std::vector<ALuint> samples_vector;
};

