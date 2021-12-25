#include "pch.h"

#include "GLRendererAPI.h"

#include <glad/glad.h>

namespace GE {

	void GLRendererAPI::setBackgroundColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRendererAPI::clear()
	{
		// can flag
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRendererAPI::draw(const std::shared_ptr<VertexArr>& vertexArr)
	{
		glDrawElements(GL_TRIANGLES, vertexArr->getIndexBuf()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

}