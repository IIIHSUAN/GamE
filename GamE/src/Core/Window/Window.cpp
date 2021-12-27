#include "pch.h"
#include "Window.h"

#ifdef GE_WINDOWS
#include "Win/Win_Window.h"  // include glfw, glad
#include "Win/Win_Input.h"
#include "Win/Win_Time.h"
#elif GE_LINUX
#include "Lin/Lin_Window.h"
#else
#error PLATFORM NOT SUPPORTED
#endif

namespace GE
{

	Window* Window::create(const WindowProperties& props)
	{
#ifdef GE_WINDOWS
		return new Win_Window(props);  //as unique_ptr
#elif GE_LINUX
		return new Lin_Window(props);  //as unique_ptr
#endif
	}

}