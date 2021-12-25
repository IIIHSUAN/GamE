#include "pch.h"
#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GE {

	void GLContext::init()
	{
		glfwMakeContextCurrent(_window);
		
		int opcode = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		COUT_ASSERT(opcode, "failed to init Glad");

		COUT_YEL("[GLContext]");
		COUT_YEL("|-- Vendor: [{0}]", glGetString(GL_VENDOR));
		COUT_YEL("|-- Renderer: [{0}]", glGetString(GL_RENDERER));
		COUT_YEL("|-- Version: [{0}]\n", glGetString(GL_VERSION));
	}

	void GLContext::swapBuffer()
	{
		glfwSwapBuffers(_window);
	}

}