#include "pch.h"
#include "Window.h"

#ifdef GE_WINDOWS
#include "Win/Win_Window.h"  // include glfw, glad
#include "Win/Win_Input.h"
#elif GE_LINUX
#include "Lin/Lin_Window.h"
#else
#error PLATFORM NOT SUPPORTED
#endif

namespace GE
{

#ifdef GE_WINDOWS
	Input* Input::_input = new Win_Input();
#elif GE_LINUX
	Input* Input::_input = nullptr;
#endif

	Window* Window::create(const WindowProperties& props)
	{
#ifdef GE_WINDOWS
		return new Win_Window(props);  //as unique_ptr
#elif GE_LINUX
		return new Lin_Window(props);  //as unique_ptr
#endif
	}

}