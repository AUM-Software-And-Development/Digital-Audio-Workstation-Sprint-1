#include "FunctionGenerator.h"

double FunctionGenerator::get_sine(int i, double frequency, int sampleRate)
{
	return sin((2 * M_PI * i * frequency) / sampleRate);
}
