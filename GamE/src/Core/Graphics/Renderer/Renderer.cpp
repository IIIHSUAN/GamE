#include "pch.h"
#include "Renderer.h"

namespace GE {

	CamMatrix& Renderer::_camMat = CamMatrix();

	void Renderer::beginDraw(OrthCamera& cam)
	{
		_camMat = cam.getMatrix();
	}
	void Renderer::submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArr>& vertexArr)
	{
		shader->bind();
		shader->uploadUniMat4("_view_project", _camMat.view_project);
	
		vertexArr->bind();
		RenderInstruction::draw(vertexArr);
	}
	void Renderer::endDraw()
	{
	}

}