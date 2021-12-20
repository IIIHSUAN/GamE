#pragma once

#ifdef GE_WINDOWS

#include "Application.h"

extern GE::Application* GE::create();

int main()
{
	GE::Application* app = GE::create();
	return 0;
}

#else
#error PLATFORM NOT SUPPORTED !
#endif 
