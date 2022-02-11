#pragma once

#ifndef QUICK_LOOK_CORE
#include "core.h"
#define QUICK_LOOK_CORE
#endif

namespace OPENGL_TEST_GROUNDS
{
	      // Exports as dll
	class AS_QUICK_LOOK_API Application
	{
	public:
		void run();

		Application();
		virtual ~Application();
	};

	// Delegated
	Application* get_and_build();
}