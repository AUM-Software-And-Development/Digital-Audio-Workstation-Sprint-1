#pragma once

#ifndef QUICK_LOOK_EXPORT_SETTINGS
#include "export_settings.h"
#define QUICK_LOOK_EXPORT_SETTINGS
#endif

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace OPENGL_TEST_GROUNDS
{
	      // Exports as dll
	class AS_QUICK_LOOK_API GLLogger
	{
	public:
		inline std::shared_ptr<spdlog::logger>& get_core_logger() { return core_logger; }
		inline std::shared_ptr<spdlog::logger>& get_client_logger() { return client_logger; }

		GLLogger();
		~GLLogger();
	private:
		std::shared_ptr<spdlog::logger> core_logger;
		std::shared_ptr<spdlog::logger> client_logger;
	};
}