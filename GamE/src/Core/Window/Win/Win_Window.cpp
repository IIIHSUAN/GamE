// for Windows' window

#include "pch.h"
#include "Win_Window.h"

#include <GLFW/glfw3.h>

namespace GE {

	static bool _isGLFWInit = false;

	static void _gLFWErrorCallback(int opcode, const char* discription)
	{
		COUT_RED("GLFW ERR Callback: ({0}) {1}", opcode, discription);
	}

	Win_Window::Win_Window(const WindowProperties& props)
	{
		init(props);
	}
	Win_Window::~Win_Window()
	{
		shutdown();
	}
	void Win_Window::init(const WindowProperties& props)
	{
		_winWindowData.title = props.title;
		_winWindowData.width = props.width;
		_winWindowData.height = props.height;
		COUT_YEL("Create Win window \"{0}\" ({1},{2})", props.title, props.width, props.height);
		

		if (!_isGLFWInit)
		{
			// glfwTerminate on sys shut down 
			int opcode = glfwInit();
			COUT_ASSERT(opcode, "failed to init GLFW");

			_isGLFWInit = true;
		}

		_gLFWwindow = glfwCreateWindow((int)props.width, (int)props.height, _winWindowData.title.c_str(), nullptr, nullptr);
		
		_context = new GLContext(_gLFWwindow);
		_context->init();

		glfwSetWindowUserPointer(_gLFWwindow, &_winWindowData);
		setVSync(true);

		// Win_Windows sets GLFW callbacks
		glfwSetWindowSizeCallback(_gLFWwindow, [](GLFWwindow* gLFWwindow, int width, int height) {
			WinWindowData& winWindowData = *(WinWindowData*)glfwGetWindowUserPointer(gLFWwindow);
			winWindowData.width = width;
			winWindowData.height = height;

			WindowResizeEvent resizeEvent(width, height);
			winWindowData.eventCallback(resizeEvent);
		});
		glfwSetWindowCloseCallback(_gLFWwindow, [](GLFWwindow* gLFWwindow) {
			WinWindowData& winWindowData = *(WinWindowData*)glfwGetWindowUserPointer(gLFWwindow);

			WindowCloseEvent closeEvent;
			winWindowData.eventCallback(closeEvent);
		});
		glfwSetKeyCallback(_gLFWwindow, [](GLFWwindow* gLFWwindow, int key, int scancode, int action, int mods) {
			WinWindowData& winWindowData = *(WinWindowData*)glfwGetWindowUserPointer(gLFWwindow);
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent e(key, 0);
				winWindowData.eventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent e(key);
				winWindowData.eventCallback(e);
				KeyPressedEvent press(key, 0);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent e(key, 1);  // Win32API not support repeatCount
				winWindowData.eventCallback(e);
				break;
			}
			}
		});
		glfwSetMouseButtonCallback(_gLFWwindow, [](GLFWwindow* gLFWwindow, int button, int action, int mods) {
			WinWindowData& winWindowData = *(WinWindowData*)glfwGetWindowUserPointer(gLFWwindow);
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e(button);
				winWindowData.eventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e(button);
				winWindowData.eventCallback(e);
				break;
			}
			}
		});
		glfwSetScrollCallback(_gLFWwindow, [](GLFWwindow* gLFWwindow, double offsetX, double offsetY) {
			WinWindowData& winWindowData = *(WinWindowData*)glfwGetWindowUserPointer(gLFWwindow);
			
			MouseScrolledEvent e((float)offsetX, (float)offsetY);
			winWindowData.eventCallback(e);
		});
		glfwSetCursorPosCallback(_gLFWwindow, [](GLFWwindow* gLFWwindow, double posX, double posY) {
			WinWindowData& winWindowData = *(WinWindowData*)glfwGetWindowUserPointer(gLFWwindow);

			MouseMovedEvent e((float)posX, (float)posY);
			winWindowData.eventCallback(e);
		});
	}
	void Win_Window::shutdown()
	{
		glfwDestroyWindow(_gLFWwindow);
	}
	void Win_Window::onUpdate()
	{
		glfwPollEvents();

		_context->swapBuffer();
	}
	void Win_Window::setVSync(bool isEnable)
	{
		glfwSwapInterval(isEnable);
		_winWindowData.vSync = isEnable;
	}
	bool Win_Window::isVSync() const
	{
		return _winWindowData.vSync;
	}
}