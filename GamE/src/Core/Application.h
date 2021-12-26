#pragma once

#include "Core/Window/Window.h"
#include "Core/Events/Event.h"
#include "Core/Layers/LayerStack.h"

#include "Core/Graphics/Shader/OpenGL/GLShader.h"
#include "Core/Graphics/Buffer/Buffer.h"
#include "Core/Graphics/Camera/Camera.h"

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

		// can have many
		std::shared_ptr<Shader> _shader, _shader2;
		std::shared_ptr<VertexArr> _vertexArr, _vertexArr2;
		//std::shared_ptr<VertexBuf> _vertexBuf;
		//std::shared_ptr<IndexBuf> _indexBuf;

		OrthCamera _cam = OrthCamera(-1.0f,1.0f,-1.0f,1.0f);
	};

	// define by client & return new Application()
	Application* create();

}