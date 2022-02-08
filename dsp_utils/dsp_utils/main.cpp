#include <stdio.h>
#include <fstream>
using namespace std;

// Remake as singleton

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

	WaveFileWriter(int sampleRate, int numberOfChannels, int bitsPerSample)
	{
		this->byte_rate = sampleRate * numberOfChannels * (bitsPerSample / this->bits_per_register);
		this->block_align = numberOfChannels * (bitsPerSample / this->bits_per_register);
	}

	void write_bytes_with_differential(ofstream& fileName, int plotHeight, int incrementalByteDifferential)
	{
		/* This is just a one liner to write an array of rounded bytes */
		fileName.write(reinterpret_cast<const char*>(&plotHeight), incrementalByteDifferential);
	}
};

#include <corecrt_math_defines.h>

class FunctionGenerator {
public:
	double get_sine(int i, double frequency, int sampleRate)
	{
		return sin((2 * M_PI * i * frequency) / sampleRate);
	}
};

int main() {

	// Make byte count defines

	int sampleRate = 44100;
	int bitDepth = 16;
	int numberOfChannels = 2;

	WaveFileWriter waveFileWrite = WaveFileWriter(sampleRate, numberOfChannels, bitDepth);

	ofstream wav;
	wav.open("sine.wav", ios::binary);
	if (wav.is_open())
	{
		// Chunk information (riff/size/format)
		wav << waveFileWrite.chunk_id;
		wav << waveFileWrite.chunk_size;
		wav << waveFileWrite.format;
		// Subchunk1
		wav << waveFileWrite.subchunk1_id;
		waveFileWrite.write_bytes_with_differential(wav, waveFileWrite.subchunk1_size, 4);
		waveFileWrite.write_bytes_with_differential(wav, waveFileWrite.audio_format, 2);
		waveFileWrite.write_bytes_with_differential(wav, numberOfChannels, 2);
		waveFileWrite.write_bytes_with_differential(wav, sampleRate, 4);
		waveFileWrite.write_bytes_with_differential(wav, waveFileWrite.byte_rate, 4);
		waveFileWrite.write_bytes_with_differential(wav, waveFileWrite.block_align, 2);
		waveFileWrite.write_bytes_with_differential(wav, bitDepth, 2);
		// Subchunk2
		wav << waveFileWrite.subchunk2_id;
		wav << waveFileWrite.subchunk2_size;
	}

	int seconds = 16;
	int amplitudeLimiter = pow(2, (bitDepth-1));
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