#include "pch.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

#define BIND_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace GE {

	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create());
		_window->setEventCallback(BIND_FUNC(Application::onEvent));

		layer_back(new Layer());
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (_isRun)
		{
			glClearColor(0, 0.05, 0.1, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : _layerStack)
				layer->onUpdate();

			_window->onUpdate();
		}
	}

	void Application::onEvent(Event & e)
	{
		EventHandler eHandler(e);
		eHandler.dispatch<WindowCloseEvent>(BIND_FUNC(Application::onWindowClose));

		COUT_TRACE("{0}", e.toString());

		for (auto it = _layerStack.end(); it != _layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (!e.isPropagation)
				break;
		}
	}

	void Application::layer_front(Layer * layer)
	{
		_layerStack.push_front(layer);
	}

	void Application::layer_back(Layer * layer)
	{
		_layerStack.push_back(layer);
	}

	bool Application::onWindowClose(WindowCloseEvent & e)
	{
		_isRun = false;
		return true;
	}

}
