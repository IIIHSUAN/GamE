#include "pch.h"
#include "Renderer.h"

namespace GE {

	void Renderer::beginDraw()
	{
	}
	void Renderer::submit(const std::shared_ptr<VertexArr>& vertexArr)
	{
		vertexArr->bind();
		RenderInstruction::draw(vertexArr);
	}
	void Renderer::endDraw()
	{
	}

}