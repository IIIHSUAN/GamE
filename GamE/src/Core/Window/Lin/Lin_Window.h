#pragma once

#include <glfw/glfw3.h>
#include "../Window.h"

namespace GE {

	class Lin_Window : public Window
	{
	public:
		Lin_Window(const WindowProperties& props);
		virtual ~Lin_Window();

		void onUpdate() override;

		unsigned int getWidth() const override { return _linWindowData.width; }
		unsigned int getHeight() const override { return _linWindowData.height; }

		// Window attributes
		void setEventCallback(const EventCallback& callback) override { _linWindowData.eventCallback = callback; }
		void setVSync(bool isEnable) override;
		bool isVSync() const override;

		virtual void* GetNativeWindow() const { return _gLFWwindow; }
	private:
		virtual void init(const WindowProperties& props);
		virtual void shutdown();
	private:
		GLFWwindow* _gLFWwindow;

		struct LinWindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallback eventCallback;  // void func(Event& e) {} ptr
		} _linWindowData;
	};

}