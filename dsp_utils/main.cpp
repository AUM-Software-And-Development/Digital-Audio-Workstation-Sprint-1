#include <stdio.h>

#include "use_math_headers.h"
#include "use_dsp_utils_namespace.h"

int main() {

	// Make byte count defines

	int sampleRate = 44100;
	int bitDepth = 16;
	int numberOfChannels = 2;

	WaveFileWriter waveFileWrite = WaveFileWriter(sampleRate, numberOfChannels, bitDepth);

	ofstream wav;
	wav.open("sine.wav", ios::binary);

	waveFileWrite.write_wav_header(wav, sampleRate, bitDepth, numberOfChannels);

	int seconds = 16;
	int amplitudeLimiter = (pow(2, (bitDepth-1))) - 1;
	double frequency = 256.0f;

	printf("Sample rate = %i\n", sampleRate);
	printf("Bit depth = %i\n", bitDepth);
	printf("Channel count = %i\n", numberOfChannels);
	printf("Seconds = %i\n", seconds);
	printf("Limiter = %i\n", amplitudeLimiter);
	printf("Frequency = %f\n", frequency);
	printf("Starting\n");

	FunctionGenerator functionGenerator;

	int pcmDataStart = wav.tellp();
	for (int i = 0; i < sampleRate * seconds; i++)
	{
		double amplitude = functionGenerator.get_sine(i, frequency, sampleRate);
		amplitude = amplitude * amplitudeLimiter / 4;

		double channel1 = amplitude;
		double channel2 = amplitude;

		waveFileWrite.write_bytes_with_differential(wav, channel1, 2);
		waveFileWrite.write_bytes_with_differential(wav, channel2, 2);
	}
	int pcmDataEnd = wav.tellp();

	// Empty size offset takes 4 bytes
	wav.seekp(pcmDataStart - 4);
	waveFileWrite.write_bytes_with_differential(wav, pcmDataEnd - pcmDataStart, 4);
	wav.seekp(4, ios::beg);
	waveFileWrite.write_bytes_with_differential(wav, pcmDataEnd - 8, 4);
	wav.close();

	return 0;
}