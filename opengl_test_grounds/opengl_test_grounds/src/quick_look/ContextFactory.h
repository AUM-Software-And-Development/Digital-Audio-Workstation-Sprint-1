/* Abstract */

#pragma once

#ifndef QUICK_LOOK_EXPORT_SETTINGS
#include "export_settings.h"
#define QUICK_LOOK_EXPORT_SETTINGS
#endif

namespace OPENGL_TEST_GROUNDS
{
	      // Exports as dll
	class AS_QUICK_LOOK_API ContextFactory
	{
	public:
		void run();

		ContextFactory();
		virtual ~ContextFactory();
		// Delegated, but this should be part of some other component class or cpp file
		virtual ContextFactory* get_and_build() { return nullptr; };
	};
}