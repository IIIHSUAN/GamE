#pragma once
#include "Core/Window/Window.h"
#include "Core/Events/Event.h"
#include "Core/Layers/LayerStack.h"

namespace GE {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void onEvent(Event& e);

		void layer_front(Layer* layer);
		void layer_back(Layer* layer);

	private:
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> _window;
		bool _isRun = true;
		LayerStack _layerStack;
	};

	// define by client & return new Application()
	Application* create();

}