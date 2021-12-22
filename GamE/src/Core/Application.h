#pragma once

#include "Core/Window/Window.h"
#include "Core/Events/Event.h"
#include "Core/Layers/LayerStack.h"

#include "Core/Shader/OpenGL/GLShader.h"
#include "Core/GraphicsData/Buffer.h"

namespace GE {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void onEvent(Event& e);

		void insert_front(Layer* layer);
		void insert_back(Layer* layer);

	private:
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> _window;
		bool _isRun = true;
		LayerStack _layerStack;

		std::unique_ptr<Shader> _shader;
		std::unique_ptr<VertexBuf> _vertexBuf;
		std::unique_ptr<IndexBuf> _indexBuf;
		unsigned int _vertexArr;
	};

	// define by client & return new Application()
	Application* create();

}