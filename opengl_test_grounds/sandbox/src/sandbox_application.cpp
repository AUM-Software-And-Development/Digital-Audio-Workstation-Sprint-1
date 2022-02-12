#ifndef QUICK_LOOK_H
#include <quick_look.h>
#define QUICK_LOOK_H
#endif // !QUICK_LOOK_H

#include "using_sandbox_namespace.h"

SandBox mainBox = SandBox();

int main(int argc, char** argv)
{
	return quick_look_main(&mainBox, 0, 0);
}