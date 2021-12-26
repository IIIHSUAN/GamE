#pragma once

#include "Core/Window/Window.h"
#include "Core/Events/Event.h"
#include "Core/Layers/LayerStack.h"

#include "Core/Graphics/Shader/OpenGL/GLShader.h"
#include "Core/Graphics/Buffer/Buffer.h"
#include "Core/Graphics/Camera/Camera.h"
#include "Core/Graphics/Renderer/Renderer.h"

namespace GE {

	class Application
	{
	public:
		Application(const WindowProperties& prop, RendererAPI::Name rendererName);
		virtual ~Application();

		void run();
		void onEvent(Event& e);

		void insert_front(Layer* layer);
		void insert_back(Layer* layer);

		inline static Application& get() { return *_application; }
		inline Window& getWindow() { return *_window; };

	private:
		static Application* _application;

		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> _window;
		bool _isRun = true;
		LayerStack _layerStack;

		// can have many _shader/_vertexArr
		//std::shared_ptr<Shader> _shader, _shader2;
		//std::shared_ptr<VertexArr> _vertexArr, _vertexArr2;  --vertexBuf, indexBuf

		//OrthCamera _cam = OrthCamera(-1.0f,1.0f,-1.0f,1.0f);
	};

	// define by client & return new Application()
	Application* create();

}