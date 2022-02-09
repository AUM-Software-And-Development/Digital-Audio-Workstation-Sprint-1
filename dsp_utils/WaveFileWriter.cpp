#include "WaveFileWriter.h"

// Remake as singleton

WaveFileWriter::WaveFileWriter(int sampleRate, int numberOfChannels, int bitsPerSample)
{
	this->byte_rate = sampleRate * numberOfChannels * (bitsPerSample / this->bits_per_register);
	this->block_align = numberOfChannels * (bitsPerSample / this->bits_per_register);
}

void WaveFileWriter::write_bytes_with_differential(ofstream& fileName, int plotHeight, int incrementalByteDifferential)
{
	/* This is just a one liner to write an array of rounded bytes */
	fileName.write(reinterpret_cast<const char*>(&plotHeight), incrementalByteDifferential);
}

void WaveFileWriter::write_wav_header(ofstream& fileName, int sampleRate, int bitsPerSample, int numberOfChannels)
{
	if (fileName.is_open())
	{
		// Chunk information (riff/size/format)
		fileName << this->chunk_id;
		fileName << this->chunk_size;
		fileName << this->format;
		// Subchunk1
		fileName << this->subchunk1_id;
		this->write_bytes_with_differential(fileName, this->subchunk1_size, 4);
		this->write_bytes_with_differential(fileName, this->audio_format, 2);
		this->write_bytes_with_differential(fileName, numberOfChannels, 2);
		this->write_bytes_with_differential(fileName, sampleRate, 4);
		this->write_bytes_with_differential(fileName, this->byte_rate, 4);
		this->write_bytes_with_differential(fileName, this->block_align, 2);
		this->write_bytes_with_differential(fileName, bitsPerSample, 2);
		// Subchunk2
		fileName << this->subchunk2_id;
		fileName << this->subchunk2_size;
	}
}
