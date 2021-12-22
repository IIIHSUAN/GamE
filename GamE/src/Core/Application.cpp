#include "pch.h"
#include "Application.h"

#include <glad/glad.h>

#define BIND_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace GE {

	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create());
		_window->setEventCallback(BIND_FUNC(Application::onEvent));

		insert_back(new Layer("Layer1"));
		insert_front(new Layer("Layer100"));
		insert_back(new Layer("Layer0"));
		insert_front(new Layer("Layer99"));

		_vertexArr.reset(VertexArr::create());

		float vertices[] {
			/*   (Float3)pos          (Float4)color   */ 
			-0.1f, -0.1f, 0.0f,		0.8f,0.1f,0.6f,1.0f,
			0.0f, 0.0f, 0.0f,		0.8f,0.4f,0.3f,1.0f,
			-0.1f, 0.1f ,0.0f,		0.9f,0.4f,0.5f,1.0f,
			0.1f, -0.1f, 0.0f,		0.8f,0.1f,0.6f,1.0f,
			0.5f, 0.1f, 0.0f,		0.8f,0.4f,0.3f,1.0f,
			-0.5f, 0.1f ,0.9f,		0.9f,0.4f,0.5f,1.0f
		};

		std::shared_ptr<VertexBuf>_vertexBuf;
		_vertexBuf.reset(VertexBuf::create(vertices, sizeof(vertices)));
		_vertexBuf->setLayout({
			{ DataType::Float3, "pos" },
			{ DataType::Float4, "color" }
		});

		_vertexArr->addVertex(_vertexBuf);

		std::shared_ptr<IndexBuf>_indexBuf;
		unsigned int indices[]{ 1,2,0,3,4,5 };
		_indexBuf.reset(IndexBuf::create(indices, sizeof(indices)/sizeof(uint32_t)));
		_vertexArr->setIndex(_indexBuf);

		std::string vertexSrc =	R"(
			#version 330 core
			layout(location=0) in vec3 _pos;
			layout(location=1) in vec4 _color;
			
			out vec3 o_pos;
			out vec4 o_color;

			void main()
			{
				o_pos = _pos;
				o_color = _color;
				gl_Position = vec4(_pos, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			layout(location=0) out vec4 _color;

			in vec3 o_pos;
			in vec4 o_color;

			void main()
			{
				_color = vec4(0.5,o_pos*0.8+0.2);
				_color = o_color;
			}
		)";
		_shader.reset(new GLShader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (_isRun)
		{
			glClearColor(0.15f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			_shader->bind();
			_vertexArr->bind();
			glDrawElements(GL_TRIANGLES, _vertexArr->getIndexBuf()->getCount(), GL_UNSIGNED_INT, nullptr);

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
