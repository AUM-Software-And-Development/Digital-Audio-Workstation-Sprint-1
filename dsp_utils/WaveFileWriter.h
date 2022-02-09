#pragma once
#ifndef MATH_HEADERS
#include "math_headers.h"
#define MATH_HEADERS
#endif // !STREAM_HEADERS_H
using namespace std;

class WaveFileWriter {
public:
	const char chunk_id[5] = { 'R','I','F','F', 0 };
	const char chunk_size[5] = { '-','-','-','-', 0 };
	const char format[5] = { 'W','A','V','E', 0 };
	const char subchunk1_id[5] = { 'f','m','t',' ', 0 };
	const int subchunk1_size = 16; // 16 is PCM (Pulse Code Modulation) AKA raw data
	const int audio_format = 1;    // 1 is PCM

	volatile int byte_rate;
	volatile int block_align;

	const char subchunk2_id[5] = { 'd','a','t','a', 0 };
	const char subchunk2_size[5] = { '-','-','-','-', 0 };

	const int bits_per_register = 8;

	WaveFileWriter(int sampleRate, int numberOfChannels, int bitsPerSample);

	void write_bytes_with_differential(ofstream& fileName, int plotHeight, int incrementalByteDifferential);
	void write_wav_header(ofstream& fileName, int sampleRate, int bitsPerSample, int numberOfChannels);
};

