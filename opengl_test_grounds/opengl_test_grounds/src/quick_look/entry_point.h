#pragma once

#ifdef QUICK_LOOK_WINDOWS_ENVIRONMENT

#include "using_opengl_test_grounds_namespace.h"

inline int quick_look_main(ContextFactory* contextFactory, int argc, char** argv)
{
	GLLogger glLogger;
	glLogger.get_core_logger()->info("Log opened.");

	printf("Starting int main from entry point of src/quick_look");
	auto quickLookSandbox = contextFactory->get_and_build();
	quickLookSandbox->run();
	delete quickLookSandbox;

	return 0;
}

#else
#error Quick look is only buildable on Windows.

#endif
