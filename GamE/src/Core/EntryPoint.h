#pragma once

#ifdef GE_WINDOWS

extern GE::Application* GE::create();

int main()
{
	GE::Log::init();

	GE::Application* app = GE::create();
	app->run();

	return 0;
}

#else
#error PLATFORM NOT SUPPORTED !
#endif 
