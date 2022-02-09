#pragma once

#include "use_math_headers.h"

namespace DSP_UTILS
{
	class FunctionGenerator {
	public:
		double get_sine(int i, double frequency, int sampleRate);
	};
}