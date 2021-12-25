#pragma once

#include "RendererAPI.h"

namespace GE {

	class Renderer
	{
	public:

		static void beginDraw();  // set camera, light, env
		static void submit(const std::shared_ptr<VertexArr>& vertexArr);  // send mesh, vertexArr info
		static void endDraw();

		virtual void flush() = 0;  // multi thread
	};

}