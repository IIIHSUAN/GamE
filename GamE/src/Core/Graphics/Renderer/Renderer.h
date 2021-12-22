#pragma once

namespace GE {

	enum class RendererAPI
	{
		None = 0, OpenGL = 1, Directx = 2
	};

	class Renderer
	{
	public:
		inline static RendererAPI getAPI() { return _API; }
	private:
		static RendererAPI _API;
	};

}