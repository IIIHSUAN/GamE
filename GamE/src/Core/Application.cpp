#include "pch.h"
#include "Application.h"

#include <glad/glad.h>

#define BIND_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace GE {

	static GLenum DataType_to_GLType(DataType type)
	{
		switch (type)
		{
		case GE::DataType::Float:
		case GE::DataType::Float2:
		case GE::DataType::Float3:
		case GE::DataType::Float4:
		case GE::DataType::Matrix3:
		case GE::DataType::Matrix4:
			return GL_FLOAT;
		case GE::DataType::Int:
		case GE::DataType::Int2:
		case GE::DataType::Int3:
		case GE::DataType::Int4:
			return GL_INT;
		case GE::DataType::Bool:
			return GL_BOOL;
		default:
			return 0;
		}
	}

	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create());
		_window->setEventCallback(BIND_FUNC(Application::onEvent));

		insert_back(new Layer("Layer1"));
		insert_front(new Layer("Layer100"));
		insert_back(new Layer("Layer0"));
		insert_front(new Layer("Layer99"));

		glGenVertexArrays(1, &_vertexArr);
		glBindVertexArray(_vertexArr);

		float vertices[] {
			/*   (Float3)pos          (Float4)color   */ 
			-0.1f, -0.1f, 0.0f,		0.8f,0.1f,0.6f,1.0f,
			0.0f, 0.0f, 0.0f,		0.8f,0.4f,0.3f,1.0f,
			-0.1f, 0.1f ,0.0f,		0.9f,0.4f,0.5f,1.0f
		};

		_vertexBuf.reset(VertexBuf::create(vertices, sizeof(vertices)));

		BufLayout _layout = {
			{ DataType::Float3, "_pos" },
			{ DataType::Float4, "_color" }
		};

		uint32_t ind = 0;
		for (const auto& buf : _layout)  // every row
		{
			glEnableVertexAttribArray(ind);
			glVertexAttribPointer(ind, buf.count(), DataType_to_GLType(buf.type), buf.isNorm, _layout.getStride(), (const void*)buf.offset);
			ind++;
		}

		unsigned int indices[3]{ 1,2,0 };
		_indexBuf.reset(IndexBuf::create(indices, sizeof(indices)/sizeof(uint32_t)));

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
			glBindVertexArray(_vertexArr);
			glDrawElements(GL_TRIANGLES, _indexBuf->getCount(), GL_UNSIGNED_INT, nullptr);

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
