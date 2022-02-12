#include "using_opengl_test_grounds_namespace.h"

GLLogger::GLLogger()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	this->core_logger = spdlog::stderr_color_mt("Quicklook");
	this->core_logger->set_level(spdlog::level::trace);
	this->client_logger = spdlog::stderr_color_mt("DAW");
	this->client_logger->set_level(spdlog::level::trace);
}
GLLogger::~GLLogger(){}