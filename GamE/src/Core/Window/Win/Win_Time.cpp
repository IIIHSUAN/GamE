#include "pch.h"
#include "Win_Time.h"

#include <GLFW/glfw3.h>

namespace GE {

	Time* Time::_time = new Win_Time();

	float Win_Time::getSeconds_impl()
	{
		return (float)glfwGetTime();
	}

}