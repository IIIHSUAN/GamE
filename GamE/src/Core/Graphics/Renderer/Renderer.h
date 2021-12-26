#pragma once

#include "RendererAPI.h"
#include "../Camera/Camera.h"

namespace GE {

	class Renderer
	{
	public:
		static void beginDraw(OrthCamera& cam);  // set camera, light, env
		static void submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArr>& vertexArr);  // send mesh, vertexArr info to shader
		static void endDraw();

		virtual void flush() = 0;  // multi thread
	private:
		static CamMatrix& _camMat;
	};

}