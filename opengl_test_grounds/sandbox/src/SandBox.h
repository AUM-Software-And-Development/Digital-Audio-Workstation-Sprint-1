#pragma once

#ifndef QUICK_LOOK_H
#include <quick_look.h>
#define QUICK_LOOK_H
#endif // !QUICK_LOOK_H

namespace SANDBOX
{
	class SandBox : public ContextFactory
	{
	public:
		SandBox();
		~SandBox();
		ContextFactory* get_and_build() override;
	};
}