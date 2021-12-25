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

		/////////////////////////////////////////////

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
				//_color = o_color;
			}
		)";
		_shader.reset(new GLShader(vertexSrc, fragmentSrc));

		/////////////////////////////////////////////

		_vertexArr2.reset(VertexArr::create());

		float vertices2[]{
			/*   (Float3)pos  */
			-0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f ,0.0f,
			0.5f, -0.5f, 0.0f
		};

		std::shared_ptr<VertexBuf>_vertexBuf2;
		_vertexBuf2.reset(VertexBuf::create(vertices2, sizeof(vertices2)));
		_vertexBuf2->setLayout({
			{ DataType::Float3, "pos" }
			});
		_vertexArr2->addVertex(_vertexBuf2);

		std::shared_ptr<IndexBuf>_indexBuf2;
		unsigned int indices2[]{ 0,1,2,0,1,3 };
		_indexBuf2.reset(IndexBuf::create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		_vertexArr2->setIndex(_indexBuf2);

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location=0) in vec3 _pos;

			void main()
			{
				gl_Position = vec4(_pos, 1.0);
			}
		)";
		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location=0) out vec4 _color;

			void main()
			{
				_color = vec4(0.6f,0.2f,0.0f,0.5f);
			}
		)";
		_shader2.reset(new GLShader(vertexSrc2, fragmentSrc2));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (_isRun)
		{
			// first

			glClearColor(0.15f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			_shader2->bind();
			_vertexArr2->bind();
			glDrawElements(GL_TRIANGLES, _vertexArr2->getIndexBuf()->getCount(), GL_UNSIGNED_INT, nullptr);

			_shader->bind();
			_vertexArr->bind();
			glDrawElements(GL_TRIANGLES, _vertexArr->getIndexBuf()->getCount(), GL_UNSIGNED_INT, nullptr);

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
