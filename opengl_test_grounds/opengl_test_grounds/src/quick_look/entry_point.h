#pragma once

#ifdef QUICK_LOOK_WINDOWS_ENVIRONMENT

#include "using_opengl_test_grounds_namespace.h"

inline int quick_look_main(ContextFactory* contextFactory, int argc, char** argv)
{
	GLLogger glLogger;

// Intentionally visible regardless of build mode
	/* Core */
#define GL_LOG_NOTIFY_USING_INFO(...)            glLogger.get_core_logger()->info(__VA_ARGS__)
#define GL_LOG_NOTIFY_USING_TRACE(...)           glLogger.get_core_logger()->trace(__VA_ARGS__)
#define GL_LOG_NOTIFY_USING_WARN(...)            glLogger.get_core_logger()->warn(__VA_ARGS__)
#define GL_LOG_NOTIFY_USING_ERROR(...)           glLogger.get_core_logger()->error(__VA_ARGS__)
#define GL_LOG_NOTIFY_USING_CRITICAL(...)        glLogger.get_core_logger()->critical(__VA_ARGS__)
    /* Client */
#define GL_LOG_NOTIFY_CLIENT_USING_INFO(...)     glLogger.get_client_logger()->info(__VA_ARGS__)
#define GL_LOG_NOTIFY_CLIENT_USING_TRACE(...)    glLogger.get_client_logger()->trace(__VA_ARGS__)
#define GL_LOG_NOTIFY_CLIENT_USING_WARN(...)     glLogger.get_client_logger()->warn(__VA_ARGS__)
#define GL_LOG_NOTIFY_CLIENT_USING_ERROR(...)    glLogger.get_client_logger()->error(__VA_ARGS__)
#define GL_LOG_NOTIFY_CLIENT_USING_CRITICAL(...) glLogger.get_client_logger()->critical(__VA_ARGS__)
/*_
  */printf("\n");
	GL_LOG_NOTIFY_USING_INFO                     ("This is an information example.");
    GL_LOG_NOTIFY_USING_TRACE                    ("This is a trace example.");
    GL_LOG_NOTIFY_USING_WARN                     ("This is a warning example.");
    GL_LOG_NOTIFY_USING_ERROR                    ("This is an error example.");
    GL_LOG_NOTIFY_USING_CRITICAL                 ("This is a critical example.");
	printf("\n\n");
	GL_LOG_NOTIFY_CLIENT_USING_INFO              ("This is a client information example.");
	GL_LOG_NOTIFY_CLIENT_USING_TRACE             ("This is a client trace example.");
	GL_LOG_NOTIFY_CLIENT_USING_WARN              ("This is a client warning example.");
	GL_LOG_NOTIFY_CLIENT_USING_ERROR             ("This is a client error example.");
	GL_LOG_NOTIFY_CLIENT_USING_CRITICAL          ("This is a client critical example.");
	

	printf("Starting int main from entry point of src/quick_look");
	auto quickLookSandbox = contextFactory->get_and_build();
	quickLookSandbox->run();
	delete quickLookSandbox;

	return 0;
}
#else
#error Quick look is only buildable on Windows.

#endif
