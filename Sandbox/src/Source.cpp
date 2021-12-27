#include <GamE.h>

namespace Sandbox {

	class Layer : public GE::Layer
	{
	public:
		Layer(const std::string name) : GE::Layer(name), _cam(-1.0f, 1.0f, -1.0f, 1.0f)
		{
			_vertexArr.reset(GE::VertexArr::create());

			float vertices[]{
				/*   (Float3)pos          (Float4)color   */
				-0.1f, -0.1f, 0.0f,		0.8f,0.1f,0.6f,1.0f,
				0.0f, 0.0f, 0.0f,		0.8f,0.4f,0.3f,1.0f,
				-0.1f, 0.1f ,0.0f,		0.9f,0.4f,0.5f,1.0f,
				0.1f, -0.1f, 0.0f,		0.8f,0.1f,0.6f,1.0f,
				0.5f, 0.1f, 0.0f,		0.8f,0.4f,0.3f,1.0f,
				-0.5f, 0.1f ,0.9f,		0.9f,0.4f,0.5f,1.0f
			};

			std::shared_ptr<GE::VertexBuf>_vertexBuf;
			_vertexBuf.reset(GE::VertexBuf::create(vertices, sizeof(vertices)));
			_vertexBuf->setLayout({
				{ GE::DataType::Float3, "pos" },
				{ GE::DataType::Float4, "color" }
				});
			_vertexArr->addVertex(_vertexBuf);

			std::shared_ptr<GE::IndexBuf>_indexBuf;
			unsigned int indices[]{ 1,2,0,1,5,0 };
			_indexBuf.reset(GE::IndexBuf::create(indices, sizeof(indices) / sizeof(uint32_t)));
			_vertexArr->setIndex(_indexBuf);

			std::string vertexSrc = R"(
				#version 330 core
				layout(location=0) in vec3 _pos;
				layout(location=1) in vec4 _color;

				uniform mat4 _view_project;
				
				out vec3 o_pos;
				out vec4 o_color;

				void main()
				{
					o_pos = _pos;
					o_color = _color;
					gl_Position = _view_project*vec4(_pos, 1.0);
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
			_shader.reset(new GE::GLShader(vertexSrc, fragmentSrc));

			/////////////////////////////////////////////

			_vertexArr2.reset(GE::VertexArr::create());

			float vertices2[]{
				/*   (Float3)pos  */
				-0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f ,0.0f,
				0.5f, -0.5f, 0.0f
			};

			std::shared_ptr<GE::VertexBuf>_vertexBuf2;
			_vertexBuf2.reset(GE::VertexBuf::create(vertices2, sizeof(vertices2)));
			_vertexBuf2->setLayout({
				{ GE::DataType::Float3, "pos" }
				});
			_vertexArr2->addVertex(_vertexBuf2);

			std::shared_ptr<GE::IndexBuf>_indexBuf2;
			unsigned int indices2[]{ 0,1,2,0,1,3 };
			_indexBuf2.reset(GE::IndexBuf::create(indices2, sizeof(indices2) / sizeof(uint32_t)));
			_vertexArr2->setIndex(_indexBuf2);

			std::string vertexSrc2 = R"(
				#version 330 core

				layout(location=0) in vec3 _pos;

				uniform mat4 _view_project;

				void main()
				{
					gl_Position = _view_project*vec4(_pos, 1.0);  // == uniform mat4
				}
			)";
			std::string fragmentSrc2 = R"(
				#version 330 core

				layout(location=0) out vec4 _color;

				void main()
				{
					_color = vec4(0.8f,0.3f,0.2f,0.5f);
				}
			)";
			_shader2.reset(new GE::GLShader(vertexSrc2, fragmentSrc2));
		}

		virtual void onUpdate(const float& delta_second) override
		{
			_actual_velocity = _velocity * delta_second, _actual_omega = _omega * delta_second;
			if(GE::Input::isKeyPressed(GE::Key::A))
				_camPos.x -= _actual_velocity;
			if (GE::Input::isKeyPressed(GE::Key::D))
				_camPos.x += _actual_velocity;
			if (GE::Input::isKeyPressed(GE::Key::S))
				_camPos.y -= _actual_velocity;
			if (GE::Input::isKeyPressed(GE::Key::W))
				_camPos.y += _actual_velocity;
			if (GE::Input::isKeyPressed(GE::Key::Q))
				_rotationDeg -= _actual_omega;
			if (GE::Input::isKeyPressed(GE::Key::E))
				_rotationDeg += _actual_omega;

			GE::RenderInstruction::setBackgroundColor({ 0.15f,0.15f,0.15f,1 });
			GE::RenderInstruction::clear();

			_cam.setPosition(_camPos);
			_cam.setRotate(_rotationDeg);

			GE::Renderer::beginDraw(_cam);
			{
				GE::Renderer::submit(_shader2, _vertexArr2);

				GE::Renderer::submit(_shader, _vertexArr);
			}
			GE::Renderer::endDraw();
		}

		virtual void onEvent(GE::Event& e) override
		{
			GE::EventHandler handler(e);
			handler.dispatch<GE::KeyPressedEvent>(BIND_FUNC(Layer::onKeyPressed));
		}

		bool onKeyPressed(GE::KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == GE::Key::Escape)
				COUT_YEL("Pressed ESC");
			return true;
		}

	private:
		std::shared_ptr<GE::Shader> _shader, _shader2;
		std::shared_ptr<GE::VertexArr> _vertexArr, _vertexArr2;
		GE::OrthCamera _cam;
		glm::vec3 _camPos{ 0.0f, 0.0f, 0.0f };
		float _velocity = 1.0f, _actual_velocity = 0.0f;

		float _omega = 2.0f, _actual_omega = 0.0f;
		float _rotationDeg = 0.0f;
	};

	class Application : public GE::Application
	{
	public:
		Application()
			: GE::Application({ "Client Window", 700, 700 }, GE::RendererAPI::Name::OpenGL)
		{
			COUT_YEL("Sandbox Init");
			insert_front(_layer);
		};
		~Application() {};
	private:
		Layer* _layer = new Layer("sandbox layer0");
	};

}

GE::Application* GE::create()
{
	return new Sandbox::Application();
}