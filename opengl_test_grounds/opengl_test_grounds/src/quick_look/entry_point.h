#pragma once

#pragma once

#ifdef QUICK_LOOK_WINDOWS_ENVIRONMENT

extern OPENGL_TEST_GROUNDS::Application* OPENGL_TEST_GROUNDS::get_and_build();

int main(int argc, char** argv)
{
	printf("Starting int main from entry point of src/quick_look");
	auto quickLookSandbox = OPENGL_TEST_GROUNDS::get_and_build();
	quickLookSandbox->run();
	delete quickLookSandbox;
}

#else
#error Quick look is only buildable on Windows.

#endif
