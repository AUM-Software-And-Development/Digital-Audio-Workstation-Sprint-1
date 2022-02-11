#include <quick_look.h>

class Sandbox : public OPENGL_TEST_GROUNDS::Application
{
public:
	Sandbox(){}
	~Sandbox(){}
};

OPENGL_TEST_GROUNDS::Application* OPENGL_TEST_GROUNDS::get_and_build()
{
	return new Sandbox();
}