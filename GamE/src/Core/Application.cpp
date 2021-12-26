#include "pch.h"
#include "Application.h"


namespace GE {

	Application* Application::_application = nullptr;

	Application::Application(const WindowProperties& prop = { "App Window", 500, 500 }, RendererAPI::Name rendererName = RendererAPI::Name::None)
	{
		if (_application != nullptr)
			COUT_ASSERT(0, "only one Application can run");
		_application = this;

		_window = std::unique_ptr<Window>(Window::create(prop));
		_window->setEventCallback(BIND_FUNC(Application::onEvent));

		RenderInstruction::init(rendererName);

		insert_back(new Layer("Layer1"));
		insert_front(new Layer("Layer100"));
		insert_back(new Layer("Layer0"));
		insert_front(new Layer("Layer99"));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (_isRun)
		{
			// first

			_window->onUpdate();

			for (Layer* layer : _layerStack)
				layer->onUpdate();

			// last
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

	void Application::insert_front(Layer * layer)
	{
		_layerStack.insert_front(layer);
	}

	void Application::insert_back(Layer * layer)
	{
		_layerStack.insert_back(layer);
	}

	bool Application::onWindowClose(WindowCloseEvent & e)
	{
		_isRun = false;
		return true;
	}

}
