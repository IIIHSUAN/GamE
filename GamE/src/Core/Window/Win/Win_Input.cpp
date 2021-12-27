#include "pch.h"
#include "Win_Input.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace GE {

	Input* Input::_input = new Win_Input();

	bool Win_Input::isKeyPressed_impl(int keyCode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getProtoWindow());
		int opcode = glfwGetKey(window, keyCode);
		return opcode == GLFW_PRESS || opcode == GLFW_REPEAT;
	}

	bool Win_Input::isMousePressed_impl(int mouseCode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getProtoWindow());
		int opcode = glfwGetMouseButton(window, mouseCode);
		return opcode == GLFW_PRESS || opcode == GLFW_REPEAT;
	}

	std::pair<float, float> Win_Input::getMousePos_impl() const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getProtoWindow());
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		return { (float)mouseX,(float)mouseY };
	}

	bool Win_Input::getMouseX_impl() const
	{
		auto[x, y] = getMousePos_impl();
		return x;
	}
	 
	bool Win_Input::getMouseY_impl() const
	{
		auto[x, y] = getMousePos_impl();
		return y;
	}

}