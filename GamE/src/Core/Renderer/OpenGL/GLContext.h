#pragma once

#include "../RendererContext.h"

struct GLFWwindow;

namespace GE {

	class GLContext: public RendererContext
	{
	public:
		GLContext(GLFWwindow* window) :_window(window) { COUT_ASSERT(_window, "glfw windows null"); }

		virtual void init() override;
		virtual void swapBuffer() override;
	private:
		GLFWwindow* _window;
	};

}