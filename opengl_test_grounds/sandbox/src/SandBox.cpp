#include "using_sandbox_namespace.h"

namespace SANDBOX
{
	SandBox::SandBox() {}

	SandBox::~SandBox() {}

	ContextFactory* SandBox::get_and_build() {
		return new SandBox();
	};
}